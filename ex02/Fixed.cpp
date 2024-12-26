/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:39:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/27 01:46:15 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

Fixed::Fixed() : fixedPointNumber_(0) {}

Fixed::Fixed(const int value) : fixedPointNumber_(value << fractionalBits_) {}

Fixed::Fixed(const float value)
    : fixedPointNumber_((int)roundf(value * (1 << fractionalBits_))) {}

Fixed::Fixed(const Fixed &other) : fixedPointNumber_(other.fixedPointNumber_) {}

Fixed &Fixed::operator=(const Fixed &other) {
  if (this != &other) {
    this->fixedPointNumber_ = other.fixedPointNumber_;
  }
  return *this;
}

Fixed::~Fixed() {}

int Fixed::getRawBits() const { return this->fixedPointNumber_; }

void Fixed::setRawBits(int const raw) { this->fixedPointNumber_ = raw; }

float Fixed::toFloat() const {
  return (float)this->fixedPointNumber_ / (1 << this->fractionalBits_);
}

int Fixed::toInt() const {
  return this->fixedPointNumber_ >> this->fractionalBits_;
}

// The 6 comparison operators: >, <, >=, <=, == and !=
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

// The 4 arithmetic operators: +,-, *, and /
Fixed Fixed::operator+(const Fixed &rhs) const {
  Fixed res;
  res.fixedPointNumber_ = this->fixedPointNumber_ + rhs.fixedPointNumber_;
  return res;
}

Fixed Fixed::operator-(const Fixed &rhs) const {
  Fixed res;
  res.fixedPointNumber_ = this->fixedPointNumber_ - rhs.fixedPointNumber_;
  return res;
}

Fixed Fixed::operator*(const Fixed &rhs) const {
  Fixed res;
  res.fixedPointNumber_ =
      static_cast<int>((static_cast<int64_t>(this->fixedPointNumber_) *
                        static_cast<int64_t>(rhs.fixedPointNumber_)) >>
                       fractionalBits_);
  return res;
}

Fixed Fixed::operator/(const Fixed &rhs) const {
  if (rhs.fixedPointNumber_ == 0) {
    throw std::runtime_error("Division by zero");
  }
  Fixed res;
  res.fixedPointNumber_ =
      (this->fixedPointNumber_ << fractionalBits_) / rhs.fixedPointNumber_;
  return res;
}

// The 4 increment/decrement (pre and post)
Fixed &Fixed::operator++() {
  this->fixedPointNumber_++;
  return *this;
}

Fixed Fixed::operator++(int) {
  Fixed tmp = *this;
  this->fixedPointNumber_++;
  return tmp;
}

Fixed &Fixed::operator--() {
  this->fixedPointNumber_--;
  return *this;
}

Fixed Fixed::operator--(int) {
  Fixed tmp = *this;
  this->fixedPointNumber_--;
  return tmp;
}

Fixed &Fixed::min(Fixed &fixed1, Fixed &fixed2) {
  return (fixed1 < fixed2) ? fixed1 : fixed2;
}

const Fixed &Fixed::min(const Fixed &fixed1, const Fixed &fixed2) {
  return (fixed1 < fixed2) ? fixed1 : fixed2;
}

Fixed &Fixed::max(Fixed &fixed1, Fixed &fixed2) {
  return (fixed1 > fixed2) ? fixed1 : fixed2;
}

const Fixed &Fixed::max(const Fixed &fixed1, const Fixed &fixed2) {
  return (fixed1 > fixed2) ? fixed1 : fixed2;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
