#ifndef LCLIB_CXX_DYNAMIC_ARRAY_HPP_2020_11_26_10_35_48
#define LCLIB_CXX_DYNAMIC_ARRAY_HPP_2020_11_26_10_35_48

#include <lclib-c++/Config.hpp>

#include <memory>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <array>
#include <algorithm>
#include <utility>
#include <tuple>

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
#include <compare>
#endif

#include <lclib-c++/bits/Helpers.hpp>
#include <lclib-c++/TypeTraits.hpp>

namespace lclib::array{

    namespace _detail{
        template<typename T> struct default_allocator{
            using type = std::allocator<T>;
        };

        template<typename T> struct default_allocator<T[]>{
            using type = std::allocator<T>;
        };
    }

    template<typename T,typename Alloc=typename _detail::default_allocator<T>::type> struct DynamicArray{
    public:
        static_assert(std::is_same_v<T,typename std::allocator_traits<Alloc>::value_type>);
        static_assert(std::is_object_v<T>);
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using allocator_type = Alloc;
        using pointer = typename std::allocator_traits<Alloc>::pointer;
        using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = typename std::iterator_traits<iterator>::difference_type;
        using size_type = std::make_unsigned_t<difference_type>;
    private:
        pointer _m_ptr;
        size_type _m_size;
        size_type _m_constructed;
        Alloc _m_alloc;
    public:
        DynamicArray(const Alloc& alloc=Alloc()) noexcept(std::is_nothrow_copy_constructible_v<Alloc>) : _m_ptr{}, _m_size{},_m_constructed{},_m_alloc{alloc}{}
        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const DynamicArray& a) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(std::allocator_traits<Alloc>::select_on_container_copy_construction(a._m_alloc)){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            this->_m_size = a._m_size;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,const U&>>* =nullptr> DynamicArray(const DynamicArray<U,Alloc2>& a,const Alloc& alloc) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            this->_m_size = a._m_size;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,U&&>>* =nullptr> DynamicArray(DynamicArray<U,Alloc2>&& a,const Alloc& alloc) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            this->_m_size = a._m_size;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,std::move(a[_m_constructed]));
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const T(&a)[N],const Alloc& alloc=Alloc()) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            this->_m_size = N;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::array<T,N>& a,const Alloc& alloc=Alloc()) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            this->_m_size = N;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::array<const T,N>& a,const Alloc& alloc=Alloc()) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            this->_m_size = N;
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::initializer_list<T>& il,const Alloc& alloc = Alloc())  : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,_m_size);
            this->_m_size = il.size();
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,il.begin()[_m_constructed]);
            }
        }

        DynamicArray(DynamicArray&& a) noexcept : _m_ptr{std::exchange(a._m_ptr,nullptr)}
            ,_m_size(std::exchange(a._m_size,0)), _m_alloc{std::move(a._m_alloc)}, _m_constructed(a._m_constructed){}


        DynamicArray(size_type n,const Alloc& alloc = Alloc()) 
            : _m_ptr{}, _m_size{}, _m_constructed{}, _m_alloc(alloc){
                this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,n);
                this->_m_size = n;
                for(;_m_constructed<_m_size;_m_constructed++)
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+this->_m_size); 
            }

        DynamicArray(size_type n,const T& t,const Alloc& alloc = Alloc()) 
            : _m_ptr{}, _m_size{}, _m_constructed{}, _m_alloc(alloc){
                this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,n);
                this->_m_size = n;
                for(;_m_constructed<_m_size;_m_constructed++)
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+this->_m_size,t); 
            }
        
        template<typename Container,std::enable_if_t<std::is_constructible_v<T,decltype(* lclib::_detail::customization::adl_and_std::begin(std::declval<Container>()))>>* =nullptr,
            std::void_t<decltype(lclib::_detail::customization::adl_and_std::size(std::declval<Container>()))>* =nullptr>
            explicit DynamicArray(Container&& container,const Alloc& alloc = Alloc()) : _m_ptr{}, _m_size(), _m_constructed{}, _m_alloc{alloc}{
                _m_ptr = std::allocator_traits<Alloc>::allocate(_m_alloc,lclib::_detail::customization::adl_and_std::size(std::forward<Container>(container)));
                _m_size = lclib::_detail::customization::adl_and_std::size(std::forward<Container>(container));
                auto iter = lclib::_detail::customization::adl_and_std::begin(std::forward<Container>(container));
                for(;_m_constructed<_m_size;_m_constructed++,iter++)
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+this->_m_constructed,*iter);

            }
        
        template<typename ForwardIterator,std::enable_if_t<
            std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIterator>::iterator_category>>* =nullptr,
            std::enable_if_t<std::is_constructible_v<T,typename std::iterator_traits<ForwardIterator>::reference>>* = nullptr>
            DynamicArray(ForwardIterator begin,ForwardIterator end,const Alloc& alloc=Alloc()) : _m_ptr{},_m_size(),_m_constructed{}, _m_alloc{alloc}{
                 _m_ptr = std::allocator_traits<Alloc>::allocate(_m_alloc,_m_size);
                 this->_m_size = std::distance(begin,end);
                for(;_m_constructed<_m_size;_m_constructed++,begin++)
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+this->_m_constructed,*begin);
            }


        ~DynamicArray(){
            if(_m_ptr){
                for(;_m_constructed>0;_m_constructed--)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
            }
        }

        reference operator[](difference_type t)noexcept{
            return _m_ptr[t];
        }

        const_reference operator[](difference_type t)const noexcept{
            return _m_ptr[t];
        }

        reference get(difference_type t){
            if(t<0||_m_constructed<=t)
                throw std::out_of_range{"index must be in-bounds for get"};
            return _m_ptr[t];
        }

        const_reference get(difference_type t)const{
            if(t<0||_m_constructed<=t)
                throw std::out_of_range{"index must be in-bounds for get"};
            return _m_ptr[t];
        }

        size_type size()const{
            return _m_size;
        }

        pointer data(){
            return _m_ptr;
        }

        const_pointer data()const{
            return _m_ptr;
        }

        iterator begin(){
            return _m_ptr;
        }

        iterator end(){
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }


        const_iterator begin()const{
            return _m_ptr;
        }

        const_iterator end()const{
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }

        const_iterator cbegin()const{
            return _m_ptr;
        }

        const_iterator cend()const{
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }

        reverse_iterator rbegin(){
            return reverse_iterator(end());
        }

        reverse_iterator rend(){
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin()const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend()const{
            return reverse_iterator(begin());
        }

        const_reverse_iterator crbegin()const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend()const{
            return reverse_iterator(begin());
        }

        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr>
        DynamicArray& operator=(const DynamicArray& arr){
            if(this==&arr)
                return *this; // No Self-assignment
            if(_m_ptr){
                for(;_m_constructed>0;_m_constructed--)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
                this->_m_ptr = nullptr; // Alloc::allocate can throw. which would cause a double-free
                this->_m_constructed = 0; // What's better, copy-initialization can throw, so reset the construction pointer
            }
            this->_m_size = arr.size();
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value){
                this->_m_alloc = arr._m_alloc;
            }
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,this->_m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,arr[_m_constructed]);
            }
            return *this;
        }

        template<std::enable_if_t<
            std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value
            || std::is_move_constructible_v<T>
        >* =nullptr> 
            DynamicArray& operator=(DynamicArray&& arr) noexcept(std::allocator_traits<Alloc>::propageate_on_container_move_assignment::value){
            if constexpr(std::allocator_traits<Alloc>::propageate_on_container_move_assignment::value){
                this->~DynamicArray();
                ::new(this) DynamicArray(std::move(arr));
                return *this;
            }else{
                if(_m_ptr){
                    for(;_m_constructed>0;_m_constructed--)
                        std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                    std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
                    this->_m_ptr = nullptr; // Alloc::allocate can throw. which would cause a double-free
                    this->_m_constructed = 0; // What's better, copy-initialization can throw, so reset the construction pointer
                }
                this->_m_size = arr.size();
                this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,this->_m_size);
                for(;_m_constructed<_m_size;_m_constructed++){
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,std::move(arr[_m_constructed]));
                }
                return *this;
            }
        }
        
        void swap(DynamicArray& arr) noexcept(std::is_nothrow_swappable_v<Alloc>||!std::allocator_traits<Alloc>::propagate_on_container_swap::value){
            using std::swap;
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_swap::value)
                swap(this->_m_alloc,arr._m_alloc);
            swap(this->_m_ptr,arr._m_ptr);
            swap(this->_m_size,arr._m_size);
            swap(this->_m_constructed,arr._m_constructed);
        }

        friend void swap(DynamicArray& a1,DynamicArray& a2) noexcept(noexcept(a1.swap(a2))){
            a1.swap(a2);
        }

        friend auto begin(DynamicArray& a)noexcept{
            return a.begin();
        }
        
        friend auto begin(const DynamicArray& a)noexcept{
            return a.begin();
        }

        friend auto end(DynamicArray& a)noexcept{
            return a.end();
        }
        
        friend auto end(const DynamicArray& a)noexcept{
            return a.end();
        }

        friend auto cbegin(const DynamicArray& a)noexcept{
            return a.cbegin();
        }

        friend auto cend(const DynamicArray& a)noexcept{
            return a.cend();
        }

        friend auto rbegin(DynamicArray& a)noexcept{
            return a.rbegin();
        }
        
        friend auto rbegin(const DynamicArray& a)noexcept{
            return a.rbegin();
        }

        friend auto rend(DynamicArray& a)noexcept{
            return a.rend();
        }
        
        friend auto rend(const DynamicArray& a)noexcept{
            return a.rend();
        }

        friend auto crbegin(const DynamicArray& a)noexcept{
            return a.crbegin();
        }

        friend auto crend(const DynamicArray& a)noexcept{
            return a.crend();
        }

        friend auto data(DynamicArray& a)noexcept{
            return a.data();
        }

        friend auto data(const DynamicArray& a)noexcept{
            return a.data();
        }

        friend auto size(const DynamicArray& a)noexcept{
            return a.size();
        }

        const Alloc& get_allocator()const noexcept{
            return this->_m_alloc;
        }
    };

    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()==std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator==(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1[0]==a2[0])){
            return std::equal(begin(a1),end(a1),begin(a2),end(a2));
        }

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()<=>std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        auto operator<=>(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2){
            return std::lexicographical_compare_three_way(begin(a1),end(a1),begin(a2),end(a2));
        }
#else
    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()==std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator!=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1==a2)){
            return !(a1==a2);
        }
#endif

    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator<(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1[0]<a2[0])){
            return std::lexicographical_compare(begin(a1),end(a1),begin(a2),end(a2));
        }

    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator>(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1[0]<a2[0])){
            return a2<a1;
        }

    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>()||std::declval<const T&>()==std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator<=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1[0]<a2[0]||a1[0]==a2[0])){
            return a1<a2||a1==a2;
        }
    template<typename T,typename Alloc1,typename Alloc2,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>()||std::declval<const T&>()==std::declval<const T&>())>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<T>[],T>>* =nullptr>
        bool operator>=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(noexcept(a1[0]<a2[0]||a1[0]==a2[0])){
            return a1>a2||a1==a2;
        }

    template<typename T,std::size_t N,std::enable_if_t<!std::is_array_v<T>>* =nullptr> DynamicArray(const T(&)[N])->DynamicArray<T>;
    template<typename T,std::size_t N,typename Alloc,std::enable_if_t<!std::is_array_v<T>>* =nullptr> DynamicArray(const T(&)[N],const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T,std::size_t N> DynamicArray(const std::array<T,N>&)->DynamicArray<T>;
    template<typename T,std::size_t N,typename Alloc> DynamicArray(const std::array<T,N>&,const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T> DynamicArray(std::initializer_list<T>) -> DynamicArray<T>;
    template<typename T,typename Alloc> DynamicArray(std::initializer_list<T>,const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T,typename Alloc1,typename Alloc2> DynamicArray(const DynamicArray<T,Alloc2>&,const Alloc1&) -> DynamicArray<T,Alloc1>;
    template<typename T,typename Alloc1,typename Alloc2> DynamicArray(DynamicArray<T,Alloc2>&&,const Alloc1&) -> DynamicArray<T,Alloc1>;

    namespace _detail{

        template<typename T> struct meets_container_requirements : std::true_type{};
        template<typename T> struct meets_container_requirements<T[]> : std::false_type{};
        template<typename T,std::size_t N> struct meets_container_requirements<T[N]> : std::false_type{};
        template<typename T,std::size_t N> struct meets_container_requirements<std::array<T,N>> : std::false_type{};
        template<typename T> struct meets_container_requirements<std::initializer_list<T>> : std::false_type{};
        template<typename T,typename Alloc> struct meets_container_requirements<DynamicArray<T,Alloc>> : std::false_type{};

        template<typename T> using detect_iterator_category = typename std::iterator_traits<T>::iterator_category;
        
    }

    template<typename Container,
        std::enable_if_t<_detail::meets_container_requirements<Container>::value>* =nullptr,
        std::void_t<decltype(lclib::_detail::customization::adl_and_std::begin(std::declval<const Container&>())),
            decltype(lclib::_detail::customization::adl_and_std::end(std::declval<const Container&>())),
            decltype(lclib::_detail::customization::adl_and_std::size(std::declval<const Container&>()))
        >* =nullptr> DynamicArray(const Container&) -> DynamicArray<decltype(*lclib::_detail::customization::adl_and_std::begin(std::declval<const Container&>()))>;

    template<typename Container,typename Alloc,
        std::enable_if_t<_detail::meets_container_requirements<Container>::value>* =nullptr,
        std::void_t<decltype(lclib::_detail::customization::adl_and_std::begin(std::declval<const Container&>())),
            decltype(lclib::_detail::customization::adl_and_std::end(std::declval<const Container&>())),
            decltype(lclib::_detail::customization::adl_and_std::size(std::declval<const Container&>()))
        >* =nullptr,
        std::enable_if_t<!std::disjunction_v<
            lclib::type_traits::is_detected<_detail::detect_iterator_category,Alloc>,
            std::is_integral<Alloc>
        >>* =nullptr> DynamicArray(const Container&,const Alloc&) -> DynamicArray<decltype(*lclib::_detail::customization::adl_and_std::begin(std::declval<const Container&>())),Alloc>;
    
    template<typename ForwardIter,std::enable_if_t<
            std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIter>::iterator_category>
        >* =nullptr,
        std::enable_if_t<!std::is_integral_v<ForwardIter>>* =nullptr>
            DynamicArray(ForwardIter,ForwardIter) -> DynamicArray<typename std::iterator_traits<ForwardIter>::element_type>;

    template<typename ForwardIter,typename Size,std::enable_if_t<
            std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIter>::iterator_category>
        >* =nullptr,
        std::enable_if_t<!std::is_integral_v<ForwardIter>>* =nullptr,
        std::enable_if_t<std::is_integral_v<Size>>* =nullptr>
            DynamicArray(ForwardIter,Size) -> DynamicArray<typename std::iterator_traits<ForwardIter>::element_type>;

    template<typename ForwardIter,typename Alloc,std::enable_if_t<
            std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIter>::iterator_category>
        >* =nullptr,
        std::enable_if_t<!std::is_integral_v<ForwardIter>>* =nullptr>
            DynamicArray(ForwardIter,ForwardIter,Alloc) -> DynamicArray<typename std::iterator_traits<ForwardIter>::element_type,Alloc>;

    template<typename ForwardIter,typename Size,typename Alloc,std::enable_if_t<
            std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIter>::iterator_category>
        >* =nullptr,
        std::enable_if_t<!std::is_integral_v<ForwardIter>>* =nullptr,
        std::enable_if_t<std::is_integral_v<Size>>* =nullptr>
            DynamicArray(ForwardIter,Size,Alloc) -> DynamicArray<typename std::iterator_traits<ForwardIter>::element_type,Alloc>;


    template<typename T,typename Alloc> struct DynamicArray<T[],Alloc>{
    public:
        static_assert(std::is_same_v<T,typename std::allocator_traits<Alloc>::value_type>);
        static_assert(std::is_object_v<T>);
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using allocator_type = Alloc;
        using pointer = typename std::allocator_traits<Alloc>::pointer;
        using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
        using difference_type = typename std::pointer_traits<pointer>::difference_type;
        using size_type = std::make_unsigned_t<difference_type>;
    private:
        pointer _m_arr;
        size_type _m_rows;
        size_type _m_cols;
        size_type _m_constructed;
        allocator_type _m_alloc;

        template<typename ref,typename const_ref> struct _slice{
            pointer _m_arr;
            size_type _m_len;

            ref operator[](difference_type i)noexcept{
                return _m_arr[i];
            }

            const_ref operator[](difference_type i)const noexcept{
                return _m_arr[i];
            }

            ref get(difference_type i){
                if(i<0||_m_len<=i)
                    throw std::out_of_range{"index to get out-of-bounds"};
                else
                    return _m_arr[i];
                
            }

            const_ref get(difference_type i)const{
                if(i<0||_m_len<=i)
                    throw std::out_of_range{"index to get out-of-bounds"};
                else
                    return _m_arr[i];
                
            }
        };

    public:
        DynamicArray(const Alloc& alloc = Alloc()) : _m_arr{}, _m_rows{}, _m_cols{}, _m_constructed{}, _m_alloc{alloc}{}

        DynamicArray(const DynamicArray& arr) : _m_arr{}, _m_rows{}, _m_cols{}, _m_constructed{}, _m_alloc{std::allocator_traits<Alloc>::select_on_container_copy_construction(arr._m_alloc)}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = arr._m_rows;
            this->_m_cols = arr._m_cols;
            for(;_m_constructed<_m_rows*_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,const_cast<const T&>(*(arr._m_arr+arr._m_constructed)));
        }

        explicit DynamicArray(const DynamicArray<T,Alloc>& arr) : _m_arr{}, _m_rows{}, _m_constructed{}, _m_alloc{std::allocator_traits<Alloc>::select_on_container_copy_construction(arr._m_alloc)}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = 1;
            this->_m_cols = arr._m_size;
            for(;_m_constructed<_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,const_cast<const T&>(*(arr._m_ptr+arr._m_constructed)));
        }

        DynamicArray(DynamicArray&& arr) : _m_arr{std::exchange(arr._m_arr,0)}, _m_rows{arr._m_rows}, _m_cols{arr._m_cols},_m_constructed{arr._m_constructed},_m_alloc{std::move(arr._m_alloc)}{}
        explicit DynamicArray(DynamicArray<T,Alloc>&& arr) : _m_arr{std::exchange(arr._m_ptr,0)}, _m_rows{1}, _m_cols{arr._m_ptr},_m_constructed{arr._m_constructed},_m_alloc{std::move(arr._m_alloc)}{}

        template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,const U&>>* =nullptr> explicit 
            DynamicArray(const DynamicArray<U[],Alloc2>& arr,const Alloc& alloc) : _m_arr{}, _m_rows{}, _m_cols{}, _m_constructed{}, _m_alloc{alloc}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = arr._m_rows;
            this->_m_cols = arr._m_cols;
            for(;_m_constructed<_m_rows*_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,const_cast<const U&>(*(arr._m_arr+arr._m_constructed)));
        }

         template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,const U&>>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<U>[],U>>* =nullptr> explicit DynamicArray(const DynamicArray<U,Alloc2>& arr) : _m_arr{}, _m_rows{}, _m_constructed{}, _m_alloc{std::allocator_traits<Alloc>::select_on_container_copy_construction(arr._m_alloc)}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = 1;
            this->_m_cols = arr._m_size;
            for(;_m_constructed<_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,const_cast<const U&>(*(arr._m_ptr+arr._m_constructed)));
        }

        template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,U&&>>* =nullptr> explicit 
            DynamicArray(DynamicArray<U[],Alloc2>&& arr,const Alloc& alloc) : _m_arr{}, _m_rows{}, _m_cols{}, _m_constructed{}, _m_alloc{alloc}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = arr._m_rows;
            this->_m_cols = arr._m_cols;
            for(;_m_constructed<_m_rows*_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,std::move(*(arr._m_arr+arr._m_constructed)));
        }

         template<typename U,typename Alloc2,std::enable_if_t<std::is_constructible_v<T,U&&>>* =nullptr,
            std::enable_if_t<!std::is_same_v<std::remove_extent_t<U>[],U>>* =nullptr> explicit DynamicArray(DynamicArray<U,Alloc2>&& arr) : _m_arr{}, _m_rows{}, _m_constructed{}, _m_alloc{std::allocator_traits<Alloc>::select_on_container_copy_construction(arr._m_alloc)}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = 1;
            this->_m_cols = arr._m_size;
            for(;_m_constructed<_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,std::move(*(arr._m_ptr+arr._m_constructed)));
        }


        explicit DynamicArray(size_type rows,size_type cols,const Alloc& alloc=Alloc()) : _m_arr{}, _m_rows{}, _m_cols{}, _m_alloc{alloc}{
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,rows*cols);
            this->_m_rows = rows;
            this->_m_cols = cols;
            for(;_m_constructed<_m_rows*_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed);
        }

        template<std::size_t N,std::size_t M> DynamicArray(const T(&arr)[N][M],const Alloc& alloc=Alloc())
             : _m_arr{}, _m_rows{}, _m_cols{}, _m_alloc{alloc}{
                 this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N*M);
                 this->_m_rows = N;
                 this->_m_cols = M;
                 for(size_type x = 0;x<N;x++)
                    for(size_type y = 0;y<M;y++,_m_constructed++)
                        std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+x*M+y,arr[x][y]);
             }

        ~DynamicArray(){
            if(_m_arr){
                while(_m_constructed-->0)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_arr+_m_constructed);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_rows*this->_m_cols);
            }
        }

        T* operator[](difference_type i){
            return _m_arr+i*_m_cols;
        }

        const T* operator[](difference_type s)const{
            return _m_arr+s*_m_cols;
        }

        _slice<reference,const_reference> get(difference_type i){
            if(i<0)
                throw std::out_of_range{"index must be in-bounds for get"};
            else if(i<_m_constructed/_m_cols)
                return {_m_arr,_m_cols};
            else if(i==_m_constructed/_m_cols)
                return {_m_arr,_m_constructed%_m_cols};
            else
                throw std::out_of_range{"index must be in-bounds for get"};
        }

        _slice<const_reference,const_reference> get(difference_type i)const{
            if(i<0)
                throw std::out_of_range{"index must be in-bounds for get"};
            else if(i<_m_constructed/_m_cols)
                return {_m_arr,_m_cols};
            else if(i==_m_constructed/_m_cols)
                return {_m_arr,_m_constructed%_m_cols};
            else
                throw std::out_of_range{"index must be in-bounds for get"};
        }

        reference get(difference_type i,difference_type j){
            if(i<0||j<0||_m_rows<=i||_m_cols<=i)
                throw std::out_of_range{"indecies must be in-bounds for get"};
            else{
                difference_type idx = i*_m_cols+j;
                if(idx<_m_constructed)
                    return _m_arr[idx];
                else
                    throw std::out_of_range{"indecies must be in-bounds for get"};
            }
        }

        const_reference get(difference_type i,difference_type j)const{
            if(i<0||j<0||_m_rows<=i||_m_cols<=i)
                throw std::out_of_range{"indecies must be in-bounds for get"};
            else{
                difference_type idx = i*_m_cols+j;
                if(idx<_m_constructed)
                    return _m_arr[idx];
                else
                    throw std::out_of_range{"indecies must be in-bounds for get"};
            }
        }

        const allocator_type& get_allocator()const{
            return _m_alloc;
        }

        size_type rows()const{
            return _m_rows;
        }

        size_type columns()const{
            return _m_cols;
        }


        pointer data(){
            return _m_arr;
        }

        const_pointer data()const{
            return _m_arr;
        }

        size_type size()const{
            return _m_rows*_m_cols;
        }

        DynamicArray& operator=(const DynamicArray& arr){
            if(_m_arr){
                while(_m_constructed-->0)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_arr+_m_constructed);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_rows*this->_m_cols);
            }
            this->_m_arr = nullptr;
            this->_m_constructed=0;
            this->_m_cols = 0;
            this->_m_rows = 0;
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value)
                this->_m_alloc = arr._m_alloc;
            this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
            this->_m_rows = 1;
            this->_m_cols = arr._m_size;
            for(;_m_constructed<_m_cols;_m_constructed++)
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,const_cast<const T&>(*(arr._m_ptr+arr._m_constructed)));
            return *this;
        }

        DynamicArray& operator=(DynamicArray&& arr) noexcept(std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value){
            if(_m_arr){
                while(_m_constructed-->0)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_arr+_m_constructed);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_rows*this->_m_cols);
            }
            this->_m_arr = nullptr;
            this->_m_constructed=0;
            this->_m_cols = 0;
            this->_m_rows = 0;
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_move_assignment){
                this->_m_alloc = std::move(arr._m_alloc);
                this->_m_arr = std::exchange(arr._m_arr,nullptr);
                this->_m_constructed = std::move(arr._m_constructed);
                this->_m_cols = std::move(arr._m_cols);
                this->_m_rows = std::move(arr._m_rows);
                return *this;
            }else{
                this->_m_arr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,arr._m_rows*arr._m_cols);
                this->_m_rows = 1;
                this->_m_cols = arr._m_size;
                for(;_m_constructed<_m_cols;_m_constructed++)
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_arr+this->_m_constructed,std::move(*(arr._m_ptr+arr._m_constructed)));
                return *this;
            }
        }

        void swap(DynamicArray& arr) noexcept(!std::allocator_traits<Alloc>::propagate_on_container_swap::value||std::is_nothrow_swappable_v<Alloc>){
            using std::swap;
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_swap::value)
                swap(_m_alloc,arr._m_alloc);
            swap(_m_arr,arr._m_arr);
            swap(_m_constructed,arr._m_constructed);
            swap(_m_rows,arr._m_rows);
            swap(_m_cols,arr._m_cols);
        }

        friend void swap(DynamicArray& a1,DynamicArray& a2) noexcept(!std::allocator_traits<Alloc>::propagate_on_container_swap::value||std::is_nothrow_swappable_v<Alloc>){
            a1.swap(a2);
        }

        
    };

    template<typename T,typename Alloc1,typename Alloc2,decltype(std::declval<const T&>()==std::declval<const T&>())* =nullptr>
         bool operator==(const DynamicArray<T[],Alloc1>& a1,const DynamicArray<T[],Alloc2>& a2) noexcept(noexcept(a1[0][0]==a2[0][0])){
            if(a1.rows()!=a2.rows()||a1.columns()!=a2.columns())
                return false;
            else
                return std::equal(a1.data(),a1.data()+a1.size(),a2.data(),a2.data()+a2.size());
        }

    template<typename T,typename Alloc1,typename Alloc2,decltype(std::declval<const T&>()==std::declval<const T&>())* =nullptr>
        bool operator!=(const DynamicArray<T[],Alloc1>& a1,const DynamicArray<T[],Alloc2>& a2) noexcept(noexcept(a1[0][0]==a2[0][0])){
            return !(a1==a2);
        }

    template<typename T,std::size_t N,std::size_t M> DynamicArray(const T(&)[N][M]) -> DynamicArray<T[]>;

    template<typename T,typename Alloc,std::size_t N,std::size_t M> DynamicArray(const T(&)[N][M],Alloc) -> DynamicArray<T[],Alloc>;
    
}

#endif