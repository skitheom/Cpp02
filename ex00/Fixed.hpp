/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:17:24 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/03 16:31:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
  int fixedPointNumber;
  static const int numOfFractionalBits = 8;

public:
  Fixed();
  Fixed(const Fixed &other);
  Fixed &operator=(const Fixed &other);
  ~Fixed();

  int getRawBits() const;
  void setRawBits(int const raw);
};

#endif
