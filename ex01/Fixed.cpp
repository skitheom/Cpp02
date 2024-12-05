/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:39:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/06 02:32:45 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed() : fixedPointNumber_(0) {
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) {
  std::cout << "Int constructor called" << std::endl;
  this->fixedPointNumber_ = value << this->fractionalBits_;
}

Fixed::Fixed(const float value) {
  std::cout << "Float constructor called" << std::endl;
  this->fixedPointNumber_ = (int)roundf(value * (1 << this->fractionalBits_));
}

Fixed::Fixed(const Fixed &other) {
  std::cout << "Copy constructor called" << std::endl;
  *this = other;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed &Fixed::operator=(const Fixed &other) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &other) {
    this->fixedPointNumber_ = other.fixedPointNumber_;
  }
  return *this;
}

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called" << std::endl;
  return this->fixedPointNumber_;
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called" << std::endl;
  this->fixedPointNumber_ = raw;
}

float Fixed::toFloat() const {
  return (float)this->fixedPointNumber_ / (1 << this->fractionalBits_);
}

int Fixed::toInt() const {
  return this->fixedPointNumber_ >> this->fractionalBits_;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
