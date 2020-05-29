//
// Created by chorm on 2020-05-28.
//

#ifndef ORKA_FRAMEWORK_BINARYIOHELPERS_HPP
#define ORKA_FRAMEWORK_BINARYIOHELPERS_HPP

#include <lclib-c++/IOWrapper.hpp>
#include <functional>

namespace lclib::io{
    template<typename T> using detect_read_from = std::void_t<decltype(std::declval<DataInputStream&>() >> std::declval<T&>())>;
    template<typename T> using detect_write_to = std::void_t<decltype(std::declval<DataOutputStream&>() << std::declval<const T&>())>;

    template<typename T,typename Predicate=std::equal_to<T>> struct MagicNumbers{
        T val;
        Predicate pred;

        template<std::void_t<
                detect_read_from<T>,
                std::enable_if_t<std::is_invocable_r_v<bool,const Predicate&,const T&,const T&>>
        >* =nullptr> friend DataInputStream& operator>>(DataInputStream& in,MagicNumbers<T,Predicate>& t){
            T _val{};
            in >> _val;
            if(!std::invoke(t.pred,t.val,_val))
                throw IOException{""};
            return in;
        }
        template<detect_write_to<T>* =nullptr>
            friend DataOutputStream& operator<<(DataOutputStream& out,const MagicNumbers<T,Predicate>& t){
                return out << t.val;
            }
    };

    template<typename Base,typename Size=typename Base::size_type> struct variable_sized{
        static_assert(type_traits::is_detected<detect_read_from,Size>::value);
        static_assert(type_traits::is_detected<detect_write_to,Size>::value);
        Base underlying;

        decltype(auto) begin(){
            using std::begin;
            return begin(underlying);
        }
        decltype(auto) end(){
            using std::end;
            return end(underlying);
        }

        decltype(auto) begin()const{
            using std::begin;
            return begin(underlying);
        }
        decltype(auto) end()const{
            using std::end;
            return end(underlying);
        }

        decltype(auto) cbegin()const{
            using std::cbegin;
            return cbegin(underlying);
        }
        decltype(auto) cend()const{
            using std::cend;
            return cend(underlying);
        }

        template<std::void_t<
                detect_read_from<Base>,
                detect_read_from<Size>
        >* =nullptr>
        friend DataInputStream& operator>>(DataInputStream& in, variable_sized& vs){
            Size sz{in.read<Size>()};
            vs.underlying.resize(sz);
            return in >> vs.underlying;
        }
        template<std::void_t<
                detect_write_to<Base>,
                detect_write_to<Size>
        >* =nullptr>
        friend DataOutputStream& operator<<(DataOutputStream& out,const variable_sized& vs){
            auto sz{vs.underlying.size()};
            if(sz>static_cast<typename Base::size_type>(std::numeric_limits<Size>::max()))
                sz = static_cast<typename Base::size_type>(std::numeric_limits<Size>::max());
            out << static_cast<Size>(sz);
            out << vs.underlying;
        }
    };


    namespace _detail{
        template<typename Tuple,std::size_t... Ns>
        void read_into(DataInputStream& in,Tuple&& tuple,std::index_sequence<Ns...>){
            (((void)(in >> std::get<Ns>(tuple))), ...,(void)0);
        }
    }

    template<typename... Ts,decltype(((std::declval<DataInputStream&>() >> std::declval<Ts&>()) , ...))* =nullptr>
    DataInputStream& operator>>(DataInputStream& in,std::tuple<Ts...>& tuple){
        _detail::read_into(in,tuple,std::make_index_sequence<sizeof...(Ts)>{});
        return in;
    }
    template<typename... Ts,decltype(((std::declval<DataInputStream&>() >> std::declval<Ts&>()) , ...))* =nullptr>
    DataInputStream& operator>>(DataInputStream& in,std::tuple<Ts&...>&& tuple){
        _detail::read_into(in,tuple,std::make_index_sequence<sizeof...(Ts)>{});
        return in;
    }

    template<typename... Ts,decltype(((void)(std::declval<DataInputStream&>() >> std::declval<Ts&>()), ...))* =nullptr>
    DataInputStream& operator>>(DataInputStream& in,std::variant<Ts...>& var){
        std::visit([&](auto& v){
            in >> v;
        },var);
        return in;
    }

    inline DataInputStream& operator>>(DataInputStream& in,std::monostate&){
        return in;
    }

    using std::begin;
    template<typename Collect,std::void_t<
                std::enable_if_t<!type_traits::is_specialization_v<variable_sized,Collect>>,
                detect_read_from<decltype(*begin(std::declval<Collect&>()))>
            >* =nullptr>
    DataInputStream& operator>>(DataInputStream& in,Collect& collect){
        for(auto& a:collect)
            in >> a;
        return in;
    }

    namespace _detail{
        template<typename Tuple,std::size_t... Ns>
        void write_to(DataOutputStream& o,const Tuple& tuple,std::index_sequence<Ns...>){
            (((void)(o << std::get<Ns>(tuple))),...,(void)0);
        }
    }

    template<typename... Ts,decltype((((void)(std::declval<DataOutputStream&>() << std::declval<const Ts&>())),...,(void)0))* =nullptr>
    DataOutputStream& operator<<(DataOutputStream& out,const std::tuple<Ts...>& tuple){
        _detail::write_to(out,tuple,std::make_index_sequence<sizeof...(Ts)>{});
    };

    template<typename... Ts,decltype((((void)(std::declval<DataOutputStream&>() << std::declval<const Ts&>())),...))* =nullptr>
    DataOutputStream& operator<<(DataOutputStream& out,const std::variant<Ts...>& variant){
        std::visit([&](const auto& v){
            out << v;
        },variant);
        return out;
    }

    inline DataOutputStream& operator<<(DataOutputStream& out,const std::monostate&){
        return out;
    }

    template<typename Collect,std::void_t<
            std::enable_if_t<!type_traits::is_specialization_v<variable_sized,Collect>>,
            detect_write_to<decltype(*begin(std::declval<const Collect&>()))>
            >* =nullptr>
    DataOutputStream& operator<<(DataOutputStream& out,const Collect& collect){
        for(const auto& a:collect)
            out << a;
        return out;
    }

    template<typename T,detect_read_from<T>* =nullptr>
        DataInputStream& operator>>(DataInputStream& in,std::optional<T>& val){
            if(val)
                return in >> *val;
            else
                return in;
        }

    template<typename T,detect_write_to<T>* =nullptr>
        DataOutputStream& operator<<(DataOutputStream& out,const std::optional<T>& val){
            if(val)
                return out << *val;
            else
                return out;
        }
}


#endif //ORKA_FRAMEWORK_BINARYIOHELPERS_HPP
