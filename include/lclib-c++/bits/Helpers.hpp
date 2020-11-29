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
                            decltype(auto) begin_(T&& t) noexcept(noexcept(begin(std::forward<T>(t)))){
                                return begin(std::forward<T>(t));
                            } 

                        template<typename T>
                            decltype(auto) end_(T&& t) noexcept(noexcept(end(std::forward<T>(t)))){
                                return end(std::forward<T>(t));
                            }
                        template<typename T>
                            auto cbegin_(const T& t) noexcept(noexcept(cbegin(t))){
                                return cbegin(t);
                            }
                        template<typename T>
                            decltype(auto) cend_(const T& t) noexcept(noexcept(cend(t))){
                                return cend(t);
                            }
                        
                        template<typename T>
                            decltype(auto) rbegin_(T&& t) noexcept(noexcept(rbegin(std::forward<T>(t)))){
                                return rbegin(std::forward<T>(t));
                            } 

                        template<typename T>
                            decltype(auto) rend_(T&& t) noexcept(noexcept(rend(std::forward<T>(t)))){
                                return rend(std::forward<T>(t));
                            }
                        template<typename T>
                            decltype(auto) crbegin_(const T& t) noexcept(noexcept(crbegin(t))){
                                return crbegin(t);
                            }
                        template<typename T>
                            decltype(auto) crend_(const T& t) noexcept(noexcept(crend(t))){
                                return crend(t);
                            }

                        template<typename T>
                            decltype(auto) size_(const T& t) noexcept(noexcept(size(t))){
                                return size(t);
                            }

                        template<typename T>
                            decltype(auto) data_(T&& t) noexcept(noexcept(data(std::forward<T>(t)))){
                                return data(std::forward<T>(t));
                            }
                    }
                }
                template<typename T> decltype(_detail::_adl::begin_(std::declval<T>())) begin(T&& t) noexcept(noexcept(_detail::_adl::begin_(std::forward<T>(t)))){
                    return _detail::_adl::begin_(t);
                }

                template<typename T> decltype(_detail::_adl::end_(std::declval<T>())) end(T&& t) noexcept(noexcept(_detail::_adl::end_(std::forward<T>(t)))){
                    return _detail::_adl::end_(t);
                }

                template<typename T> decltype(_detail::_adl::cbegin_(std::declval<const T&>())) cbegin(const T& t) noexcept(noexcept(_detail::_adl::cbegin_(t))){
                    return _detail::_adl::cbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::cend_(std::declval<const T&>())) cend(const T& t) noexcept(noexcept(_detail::_adl::cend_(t))){
                    return _detail::_adl::cend_(t);
                }

                template<typename T> decltype(_detail::_adl::rbegin_(std::declval<T>())) rbegin(T&& t) noexcept(noexcept(_detail::_adl::rbegin_(std::forward<T>(t)))){
                    return _detail::_adl::rbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::rend_(std::declval<T>())) rend(T&& t) noexcept(noexcept(_detail::_adl::rend_(std::forward<T>(t)))){
                    return _detail::_adl::end_(t);
                }

                template<typename T> decltype(_detail::_adl::crbegin_(std::declval<const T&>())) crbegin(const T& t) noexcept(noexcept(_detail::_adl::crbegin_(t))){
                    return _detail::_adl::crbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::crend_(std::declval<const T&>())) crend(const T& t) noexcept(noexcept(_detail::_adl::crend_(t))){
                    return _detail::_adl::crend_(t);
                }

                template<typename T,typename U> decltype(_detail::_adl::swap_(std::declval<T&>(),std::declval<U&>())) swap(T& t,U& u) noexcept(noexcept(_detail::_adl::swap_(t,u))){
                    return _detail::_adl::swap_(t,u);
                }

                template<typename T> decltype(_detail::_adl::size_(std::declval<const T&>())) size(const T& t) noexcept(noexcept(_detail::_adl::size_(t))){
                    return _detail::_adl::size_(t);
                }

                template<typename T> decltype(_detail::_adl::data_(std::declval<T>())) data(T&& t) noexcept(noexcept(_detail::_adl::data_(std::forward<T>(t)))){
                    return _detail::_adl::data_(std::forward<T>(t));
                }


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
                            decltype(end(std::declval<T>())) begin_(T&& t) noexcept(noexcept(begin(std::forward<T>(t)))){
                                return begin(std::forward<T>(t));
                            } 

                        template<typename T>
                            decltype(end(std::declval<T>())) end_(T&& t) noexcept(noexcept(end(std::forward<T>(t)))){
                                return end(std::forward<T>(t));
                            }
                        template<typename T>
                            decltype(cbegin(std::declval<const T&>())) cbegin_(const T& t) noexcept(noexcept(cbegin(t))){
                                return cbegin(t);
                            }
                        template<typename T>
                            decltype(cend(std::declval<const T&>())) cend_(const T& t) noexcept(noexcept(cend(t))){
                                return cend(t);
                            }
                        
                        template<typename T>
                            decltype(rbegin(std::declval<T>())) rbegin_(T&& t) noexcept(noexcept(rbegin(std::forward<T>(t)))){
                                return rbegin(std::forward<T>(t));
                            } 

                        template<typename T>
                            decltype(rend(std::declval<T>())) rend_(T&& t) noexcept(noexcept(rend(std::forward<T>(t)))){
                                return rend(std::forward<T>(t));
                            }
                        template<typename T>
                            decltype(crbegin(std::declval<const T&>())) crbegin_(const T& t) noexcept(noexcept(crbegin(t))){
                                return crbegin(t);
                            }
                        template<typename T>
                            decltype(crend(std::declval<const T&>())) crend_(const T& t) noexcept(noexcept(crend(t))){
                                return crend(t);
                            }

                        template<typename T>
                            decltype(auto) size_(const T& t) noexcept(noexcept(size(t))){
                                return size(t);
                            }

                        template<typename T>
                            decltype(auto) data_(T&& t) noexcept(noexcept(data(std::forward<T>(t)))){
                                return data(std::forward<T>(t));
                            }
                    }
                }
                template<typename T> decltype(_detail::_adl::begin_(std::declval<T>())) begin(T&& t) noexcept(noexcept(_detail::_adl::begin_(std::forward<T>(t)))){
                    return _detail::_adl::begin_(t);
                }

                template<typename T> decltype(_detail::_adl::end_(std::declval<T>())) end(T&& t) noexcept(noexcept(_detail::_adl::end_(std::forward<T>(t)))){
                    return _detail::_adl::end_(t);
                }

                template<typename T> decltype(_detail::_adl::cbegin_(std::declval<const T&>())) cbegin(const T& t) noexcept(noexcept(_detail::_adl::cbegin_(t))){
                    return _detail::_adl::cbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::cend_(std::declval<const T&>())) cend(const T& t) noexcept(noexcept(_detail::_adl::cend_(t))){
                    return _detail::_adl::cend_(t);
                }

                template<typename T> decltype(_detail::_adl::rbegin_(std::declval<T>())) rbegin(T&& t) noexcept(noexcept(_detail::_adl::rbegin_(std::forward<T>(t)))){
                    return _detail::_adl::rbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::rend_(std::declval<T>())) rend(T&& t) noexcept(noexcept(_detail::_adl::rend_(std::forward<T>(t)))){
                    return _detail::_adl::end_(t);
                }

                template<typename T> decltype(_detail::_adl::crbegin_(std::declval<const T&>())) crbegin(const T& t) noexcept(noexcept(_detail::_adl::crbegin_(t))){
                    return _detail::_adl::crbegin_(t);
                }

                template<typename T> decltype(_detail::_adl::crend_(std::declval<const T&>())) crend(const T& t) noexcept(noexcept(_detail::_adl::crend_(t))){
                    return _detail::_adl::crend_(t);
                }

                template<typename T,typename U> decltype(_detail::_adl::swap_(std::declval<T&>(),std::declval<U&>())) swap(T& t,U& u) noexcept(noexcept(_detail::_adl::swap_(t,u))){
                    return _detail::_adl::swap_(t,u);
                }

                template<typename T> decltype(_detail::_adl::size_(std::declval<const T&>())) size(const T& t) noexcept(noexcept(_detail::_adl::size_(t))){
                    return _detail::_adl::size_(t);
                }

                template<typename T> decltype(_detail::_adl::data_(std::declval<T>())) data(T&& t) noexcept(noexcept(_detail::_adl::data_(std::forward<T>(t)))){
                    return _detail::_adl::data_(std::forward<T>(t));
                }
            }

        }
    }
}

#endif