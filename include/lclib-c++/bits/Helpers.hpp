#ifndef LCLIBCXX_BITS_HELPERS_HPP_2020_10_14_09_49_31_
#define LCLIBCXX_BITS_HELPERS_HPP_2020_10_14_09_49_31_

#include <utility>


namespace lclib{
    namespace _detail{
        namespace customization{
            namespace adl_and_std{
                namespace _detail{
                    using namespace std; // Very specific case this is allowed
                    namespace _adl{
                        template<typename T,typename U,decltype(swap(std::declval<T&>(),std::declval<U&>()))* =nullptr>
                             void swap_(T& t1,U& t2) noexcept(noexcept(swap(std::declval<T&>(),std::declval<U&>()))){
                                swap(t1,t2);
                             }

                        template<typename T>
                            auto begin_(T& t) noexcept(noexcept(begin(t))) -> decltype(begin(t)){
                                return begin(t);
                            } 

                        template<typename T>
                            auto end_(T& t) noexcept(noexcept(end(t))) -> decltype(end(t)){
                                return end(t);
                            }
                        template<typename T>
                            auto cbegin_(const T& t) noexcept(noexcept(cbegin(t))) -> decltype(cbegin(t)){
                                return cbegin(t);
                            }
                        template<typename T>
                            auto cend_(T& t) noexcept(noexcept(cend(t))) -> decltype(cend(t)){
                                return cend(t);
                            }
                        
                        template<typename T>
                            auto rbegin_(T& t) noexcept(noexcept(rbegin(t))) -> decltype(rbegin(t)){
                                return rbegin(t);
                            } 

                        template<typename T>
                            auto rend_(T& t) noexcept(noexcept(rend(t))) -> decltype(rend(t)){
                                return end(t);
                            }
                        template<typename T>
                            auto crbegin_(const T& t) noexcept(noexcept(crbegin(t))) -> decltype(crbegin(t)){
                                return crbegin(t);
                            }
                        template<typename T>
                            auto crend_(const T& t) noexcept(noexcept(crend(t))) -> decltype(crend(t)){
                                return crend(t);
                            }
                    }
                }
                constexpr auto swap = [](auto& a,auto& b) noexcept(noexcept(_detail::_adl::swap_(a,b)))
                -> decltype(_detail::_adl::swap_(a,b)){
                    _detail::_adl::swap_(a,b);
                };

                constexpr auto begin = [](auto& a) noexcept(noexcept(_detail::_adl::begin_(a)))
                -> decltype(_detail::_adl::begin_(a)){
                    return _detail::_adl::begin_(a);
                };
                constexpr auto end = [](auto& a) noexcept(noexcept(_detail::_adl::end_(a)))
                -> decltype(_detail::_adl::end_(a)){
                    return _detail::_adl::end_(a);
                };
                constexpr auto cbegin = [](const auto& a) noexcept(noexcept(_detail::_adl::cbegin_(a)))
                -> decltype(_detail::_adl::cbegin_(a)){
                    return _detail::_adl::cbegin_(a);
                };
                constexpr auto cend = [](const auto& a) noexcept(noexcept(_detail::_adl::cend_(a)))
                -> decltype(_detail::_adl::cend_(a)){
                    return _detail::_adl::cend_(a);
                };
                constexpr auto rbegin = [](auto& a) noexcept(noexcept(_detail::_adl::rbegin_(a)))
                -> decltype(_detail::_adl::rbegin_(a)){
                    return _detail::_adl::rbegin_(a);
                };
                constexpr auto rend = [](auto& a) noexcept(noexcept(_detail::_adl::rend_(a)))
                -> decltype(_detail::_adl::rend_(a)){
                    return _detail::_adl::rend_(a);
                };
                constexpr auto crbegin = [](const auto& a) noexcept(noexcept(_detail::_adl::crbegin_(a)))
                -> decltype(_detail::_adl::crbegin_(a)){
                    return _detail::_adl::crbegin_(a);
                };
                constexpr auto crend = [](const auto& a) noexcept(noexcept(_detail::_adl::crend_(a)))
                -> decltype(_detail::_adl::crend_(a)){
                    return _detail::_adl::crend_(a);
                };
            }
            namespace adl_only{
                namespace _detail{
                    template<typename T,typename U> void swap(T&,U&)=delete;
                    template<typename T> void begin(T&)=delete;
                    template<typename T> void end(T&)=delete;
                    template<typename T> void cbegin(T&)=delete;
                    template<typename T> void cend(T&)=delete;
                    template<typename T> void rbegin(T&)=delete;
                    template<typename T> void rend(T&)=delete;
                    template<typename T> void crbegin(T&)=delete;
                    template<typename T> void crend(T&)=delete;
                    namespace _adl{
                        template<typename T,typename U,decltype(swap(std::declval<T&>(),std::declval<U&>()))* =nullptr>
                             void swap_(T& t1,U& t2) noexcept(noexcept(swap(std::declval<T&>(),std::declval<U&>()))){
                                swap(t1,t2);
                             }

                        template<typename T>
                            auto begin_(T& t) noexcept(noexcept(begin(t))) -> decltype(begin(t)){
                                return begin(t);
                            } 

                        template<typename T>
                            auto end_(T& t) noexcept(noexcept(end(t))) -> decltype(end(t)){
                                return end(t);
                            }
                        template<typename T>
                            auto cbegin_(const T& t) noexcept(noexcept(cbegin(t))) -> decltype(cbegin(t)){
                                return cbegin(t);
                            }
                        template<typename T>
                            auto cend_(T& t) noexcept(noexcept(cend(t))) -> decltype(cend(t)){
                                return cend(t);
                            }
                        
                        template<typename T>
                            auto rbegin_(T& t) noexcept(noexcept(rbegin(t))) -> decltype(rbegin(t)){
                                return rbegin(t);
                            } 

                        template<typename T>
                            auto rend_(T& t) noexcept(noexcept(rend(t))) -> decltype(rend(t)){
                                return end(t);
                            }
                        template<typename T>
                            auto crbegin_(const T& t) noexcept(noexcept(crbegin(t))) -> decltype(crbegin(t)){
                                return crbegin(t);
                            }
                        template<typename T>
                            auto crend_(const T& t) noexcept(noexcept(crend(t))) -> decltype(crend(t)){
                                return crend(t);
                            }
                    }
                }
                constexpr auto swap = [](auto& a,auto& b) noexcept(noexcept(_detail::_adl::swap_(a,b)))
                -> decltype(_detail::_adl::swap_(a,b)){
                    _detail::_adl::swap_(a,b);
                };

                constexpr auto begin = [](auto& a) noexcept(noexcept(_detail::_adl::begin_(a)))
                -> decltype(_detail::_adl::begin_(a)){
                    return _detail::_adl::begin_(a);
                };
                constexpr auto end = [](auto& a) noexcept(noexcept(_detail::_adl::end_(a)))
                -> decltype(_detail::_adl::end_(a)){
                    return _detail::_adl::end_(a);
                };
                constexpr auto cbegin = [](const auto& a) noexcept(noexcept(_detail::_adl::cbegin_(a)))
                -> decltype(_detail::_adl::cbegin_(a)){
                    return _detail::_adl::cbegin_(a);
                };
                constexpr auto cend = [](const auto& a) noexcept(noexcept(_detail::_adl::cend_(a)))
                -> decltype(_detail::_adl::cend_(a)){
                    return _detail::_adl::cend_(a);
                };
                constexpr auto rbegin = [](auto& a) noexcept(noexcept(_detail::_adl::rbegin_(a)))
                -> decltype(_detail::_adl::rbegin_(a)){
                    return _detail::_adl::rbegin_(a);
                };
                constexpr auto rend = [](auto& a) noexcept(noexcept(_detail::_adl::rend_(a)))
                -> decltype(_detail::_adl::rend_(a)){
                    return _detail::_adl::rend_(a);
                };
                constexpr auto crbegin = [](const auto& a) noexcept(noexcept(_detail::_adl::crbegin_(a)))
                -> decltype(_detail::_adl::crbegin_(a)){
                    return _detail::_adl::crbegin_(a);
                };
                constexpr auto crend = [](const auto& a) noexcept(noexcept(_detail::_adl::crend_(a)))
                -> decltype(_detail::_adl::crend_(a)){
                    return _detail::_adl::crend_(a);
                };
            }

        }
    }
}

#endif