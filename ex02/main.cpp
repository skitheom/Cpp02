/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:09:37 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/27 01:32:21 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

static void div_zero_test(void) {
  std::cout << "\n<< Test division by zero >>" << std::endl;
  try {
    Fixed a(5.0f);
    Fixed b(0.0f);
    Fixed c = a / b;
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }
}

static void testAllOperators() {
  std::cout << "\n<< Testing all operators >>" << std::endl;

  Fixed a(4.2f);
  Fixed b(7.0f);
  Fixed c(4.2f);

  std::cout << "Current a: " << a << std::endl;
  std::cout << "Current b: " << b << std::endl;
  std::cout << "Current c: " << c << std::endl;

  std::cout << "Comparison operators:" << std::endl;
  std::cout << "a > b: " << (a > b) << std::endl;
  std::cout << "a < b: " << (a < b) << std::endl;
  std::cout << "a >= c: " << (a >= c) << std::endl;
  std::cout << "a <= b: " << (a <= b) << std::endl;
  std::cout << "a == c: " << (a == c) << std::endl;
  std::cout << "a != b: " << (a != b) << std::endl;

  std::cout << "\nArithmetic operators:" << std::endl;
  Fixed sum = a + b;
  Fixed diff = b - a;
  Fixed prod = a * b;
  Fixed quot = b / a;

  std::cout << "a + b: " << sum << std::endl;
  std::cout << "b - a: " << diff << std::endl;
  std::cout << "a * b: " << prod << std::endl;
  std::cout << "b / a: " << quot << std::endl;

  std::cout << "\nIncrement and decrement operators:" << std::endl;
  std::cout << "Pre-increment ++a: " << ++a << std::endl;
  std::cout << "Post-increment a++: " << a++ << std::endl;
  std::cout << "Current a: " << a << std::endl;
  std::cout << "Pre-decrement --a: " << --a << std::endl;
  std::cout << "Post-decrement a--: " << a-- << std::endl;
  std::cout << "Current a: " << a << std::endl;

  std::cout << "\nMin and max functions:" << std::endl;
  Fixed &minVal = Fixed::min(a, b);
  const Fixed &constMinVal = Fixed::min(c, b);
  Fixed &maxVal = Fixed::max(a, b);
  const Fixed &constMaxVal = Fixed::max(c, b);

  std::cout << "Min of a and b: " << minVal << std::endl;
  std::cout << "Const Min of c and b: " << constMinVal << std::endl;
  std::cout << "Max of a and b: " << maxVal << std::endl;
  std::cout << "Const Max of c and b: " << constMaxVal << std::endl;
}

static void simpleTest(void) {

  std::cout << "<< Simple test >>" << std::endl;
  Fixed a;
  Fixed const b(Fixed(5.05f) * Fixed(2));
  std::cout << a << std::endl;
  std::cout << ++a << std::endl;
  std::cout << a << std::endl;
  std::cout << a++ << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << Fixed::max(a, b) << std::endl;
}

int main(void) {
  simpleTest();
  testAllOperators();
  div_zero_test();
  return 0;
}
