/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:17:24 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/06 01:35:12 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
  int fixedPointNumber_;
  static const int fractionalBits_ = 8;

public:
  Fixed();
  Fixed(const int value);
  Fixed(const float value);
  Fixed(const Fixed &other);
  ~Fixed();
  Fixed &operator=(const Fixed &other);

  int getRawBits() const;
  void setRawBits(int const raw);

  float toFloat() const;
  int toInt() const;
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif
