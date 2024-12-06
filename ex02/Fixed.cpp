/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:39:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/07 00:17:24 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

Fixed::Fixed() : fixedPointNumber_(0) {}

Fixed::Fixed(const int value) {
  this->fixedPointNumber_ = value << this->fractionalBits_;
}

Fixed::Fixed(const float value) {
  this->fixedPointNumber_ = (int)roundf(value * (1 << this->fractionalBits_));
}

Fixed::Fixed(const Fixed &other) { *this = other; }

Fixed::~Fixed() {}

Fixed &Fixed::operator=(const Fixed &other) {
  if (this != &other) {
    this->fixedPointNumber_ = other.fixedPointNumber_;
  }
  return *this;
}

int Fixed::getRawBits() const { return this->fixedPointNumber_; }

void Fixed::setRawBits(int const raw) { this->fixedPointNumber_ = raw; }

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

Fixed Fixed::operator+(const Fixed &rhs) const {
  return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed &rhs) const {
  return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed &rhs) const {
  return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed &rhs) const {
  if (rhs.toFloat() == 0) {
    throw std::runtime_error("Division by zero");
  }
  return Fixed(this->toFloat() / rhs.toFloat());
}

bool Fixed::operator>(const Fixed &rhs) const {
  return (this->getRawBits() > rhs.getRawBits());
}

bool Fixed::operator<(const Fixed &rhs) const {
  return (this->getRawBits() < rhs.getRawBits());
}

bool Fixed::operator>=(const Fixed &rhs) const {
  return (this->getRawBits() >= rhs.getRawBits());
}

bool Fixed::operator<=(const Fixed &rhs) const {
  return (this->getRawBits() <= rhs.getRawBits());
}

bool Fixed::operator==(const Fixed &rhs) const {
  return (this->getRawBits() == rhs.getRawBits());
}

bool Fixed::operator!=(const Fixed &rhs) const {
  return (this->getRawBits() != rhs.getRawBits());
}
