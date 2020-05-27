#ifndef LCLIB_CXX_TYPETRAITS_HPP_2019_10_29__14_33
#define LCLIB_CXX_TYPETRAITS_HPP_2019_10_29__14_33

#include <type_traits>
#include <cstddef>

namespace lightningcreations::lclib::type_traits{

    struct empty{};

    template<typename T> struct type_identity{
        typedef T type;
    };

    template<typename T> using type_identity_t = typename type_identity<T>::type;

    namespace _detail{
        template<template<typename...> typename to_instantiate,typename... Ts>
            auto check_instantiate(std::void_t<to_instantiate<Ts...>>*) -> type_identity<to_instantiate<Ts...>>;

        template<template<typename...> typename to_instantiate,typename... Ts>
            auto check_instantiate(...) -> empty;

        template<template<typename...> typename to_instantiate,typename... Ts>
            using checked_instantiate = decltype(check_instantiate<to_instantiate,Ts...>(nullptr));
    }

    template<bool b,template<typename...> typename if_true,template<typename...> typename if_false,typename... Ts>
        struct conditional_substitute : _detail::checked_instantiate<if_true,Ts...> {};
    template<template<typename...> typename if_true,template<typename...> typename if_false,typename... Ts>
    struct conditional_substitute<false,if_true,if_false,Ts...> : _detail::checked_instantiate<if_false,Ts...> {};

    template<bool b,template<typename...> typename if_true,template<typename...> typename if_false,typename... Ts> using conditional_substitute_t =
            typename conditional_substitute<b,if_true,if_false,Ts...>::type;



    template<auto val> using auto_constant = std::integral_constant<decltype(val),val>;

    template<typename...> using always_false = std::false_type;
    template<typename...> using always_true = std::true_type;

    namespace _detail {
        template <class Default, class AlwaysVoid,
                template<class...> class Op, class... Args>
        struct detector {
            using value_t = std::false_type;
            using type = Default;
        };

        template <class Default, template<class...> class Op, class... Args>
        struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
            using value_t = std::true_type;
            using type = Op<Args...>;
        };

    } // namespace _detail
    struct nonesuch {
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };
    template <template<class...> class Op, class... Args>
    using is_detected = typename _detail::detector<nonesuch, void, Op, Args...>::value_t;

    template <template<class...> class Op, class... Args>
    using detected_t = typename _detail::detector<nonesuch, void, Op, Args...>::type;

    template <class Default, template<class...> class Op, class... Args>
    using detected_or = _detail::detector<Default, void, Op, Args...>;

    template<typename... Ts> struct has_common_type : std::false_type{};

    namespace _detail{
        template<typename T,typename U> std::true_type check_common_type(std::common_type_t<T,U>*);
        template<typename,typename> std::false_type check_common_type(...);


        template<typename T,typename U> using check_has_common_type_t = decltype(check_common_type<T,U>(nullptr));
        template<typename T,typename U> struct sub_convertible_to_common_type : std::conjunction<std::is_convertible<T,std::common_type_t<T,U>>,std::is_convertible<U,std::common_type_t<T,U>>>{};
        template<typename T,typename U> struct sub_same_common_type : std::is_same<std::common_type_t<T,U>,std::common_type_t<U,T>>{};

        template<typename S,typename T,typename U> struct sub_common_between:
            std::conjunction<has_common_type<std::common_type_t<S,T>,std::common_type_t<T,U>>,
            has_common_type<std::common_type_t<S,U>,std::common_type_t<S,T>>>{};

        template<typename S, typename T,typename U,typename... Rs> struct sub_check_common :
            has_common_type<std::common_type_t<S,T,U>,std::common_type_t<Rs...>>{};
    }



    template<> struct has_common_type<> : std::true_type{};
    template<typename T> struct has_common_type<T> : std::true_type{};
    template<typename T,typename U> struct has_common_type<T,U> : std::conjunction<
            conditional_substitute_t<_detail::check_has_common_type_t<T,U>::value,_detail::sub_same_common_type,always_false,T,U>,
            conditional_substitute_t<_detail::check_has_common_type_t<T,U>::value,_detail::sub_convertible_to_common_type,always_false,T,U>>{};
    template<typename S,typename T,typename U> struct has_common_type<S,T,U> :
            conditional_substitute_t<std::conjunction_v<has_common_type<S,T>,has_common_type<T,U>,has_common_type<S,U>>,
            _detail::sub_common_between,always_false,S,T,U>{};
    template<typename S,typename T,typename U,typename... Rs>
        struct has_common_type<S,T,U,Rs...> :
            conditional_substitute_t<std::conjunction_v<has_common_type<S,T,U>,has_common_type<Rs...>>,
            _detail::sub_check_common,always_false,S,T,U,Rs...>{};

    template<typename... Ts> constexpr bool has_common_type_v = has_common_type<Ts...>::value;

    template<typename T> struct is_byte : std::false_type{};
    template<> struct is_byte<unsigned char> : std::true_type{};
    template<> struct is_byte<std::byte> : std::true_type{};

    template<typename T> struct is_byte<volatile T> : is_byte<T>{};
    template<typename T> struct is_byte<const T> : is_byte<T>{};
    template<typename T> struct is_byte<const volatile T> : is_byte<T>{};

    template<typename T> constexpr bool is_byte_v = is_byte<T>::value;

    template<typename T> struct is_char : std::false_type{};
    template<> struct is_char<char>: std::true_type{};
    template<> struct is_char<wchar_t>:std::true_type{};
    template<> struct is_char<char16_t>:std::true_type{};
    template<> struct is_char<char32_t>:std::true_type{};
#ifdef __cpp_char8_t
    template<> struct is_char<char8_t>:std::true_type{};
#endif

    template<typename T> struct is_char<const T>:is_char<T>{};
    template<typename T> struct is_char<volatile T>:is_char<T>{};
    template<typename T> struct is_char<const volatile T>:is_char<T>{};

    template<typename T> constexpr bool is_char_v = is_char<T>::value;

    template<typename T> struct is_cstring : std::false_type{};
    template<typename T,std::size_t N> struct is_cstring<T[N]> : is_char<T>{};
    template<typename T> struct is_cstring<T[]> : is_char<T>{};
    template<typename T> struct is_cstring<T*> : is_char<T>{};
    template<typename T> struct is_cstring<T&> : is_cstring<T>{};
    template<typename T> struct is_cstring<T&&> : is_cstring<std::remove_reference_t<T>>{};
    template<typename T> struct is_cstring<const T> : is_cstring<T>{};
    template<typename T> struct is_cstring<volatile T>: is_cstring<T>{};
    template<typename T> struct is_cstring<const volatile T> : is_cstring<T>{};

    template<typename T> constexpr bool is_cstring_v = is_cstring<T>::value;

    namespace _detail{

        template<typename T,typename... Args>
            std::true_type check_is_list_constructible_helper(std::void_t<decltype(T{std::declval<Args>()...})>*);
        template<typename,typename...>
            std::false_type check_is_list_constructible_helper(...);
        template<typename T,typename... Args> using check_is_list_constructible =
        decltype(check_is_list_constructible_helper<T,Args...>(nullptr));
    }

    template<typename T,typename... Args> struct is_list_constructible : _detail::check_is_list_constructible<T,Args...>{};

    template<typename T,typename... Args> constexpr const bool is_list_constructible_v = is_list_constructible<T,Args...>::value;
    template<typename T,typename U> struct is_list_convertible : std::conjunction<is_list_constructible<T,U>,std::is_convertible<U,T>>{};

    template<template<typename...> class Template,typename Type> struct is_specialization:std::false_type{};
    template<template<typename...> class Template,typename... Args>
        struct is_specialization<Template,Template<Args...>>:std::true_type{};
    template<template<typename...> class Template,typename Type>
        constexpr bool is_specialization_v = is_specialization<Template,Type>::value;
}



#endif