/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:09:37 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/27 01:50:14 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

static void test1() {
  Point a(0.0f, 0.0f);
  Point b(1.0f, 0.0f);
  Point c(0.0f, 1.0f);

  Point inside(0.2f, 0.2f);
  Point onEdge(0.5f, 0.0f);
  Point vertex(0.0f, 0.0f);
  Point outside(1.0f, 1.0f);

  std::cout << "Inside: " << bsp(a, b, c, inside) << std::endl;
  std::cout << "On Edge: " << bsp(a, b, c, onEdge) << std::endl;
  std::cout << "Vertex: " << bsp(a, b, c, vertex) << std::endl;
  std::cout << "Outside: " << bsp(a, b, c, outside) << std::endl;
}

static void test2() {
  Point a(0.0f, 0.0f);
  Point b(1.0f, 0.0f);
  Point c(2.0f, 0.0f);

  Point p0(1.0f, 0.0f);
  Point p1(1.0f, 1.0f);

  std::cout << "Not triangle: " << bsp(a, b, c, p0) << std::endl;
  std::cout << "Not triangle: " << bsp(a, b, c, p1) << std::endl;
}

static void test3() {

  Point a(0.0f, 0.0f);
  Point b(1.0f, 1.0f);
  Point c(2.0f, 0.0f);

  Point pointOnEdge(1.0f, 0.0f);

  std::cout << "On Edge: " << bsp(a, b, c, pointOnEdge) << std::endl;

  Point pointInside(1.0f, 0.5f);

  std::cout << "Inside: " << bsp(a, b, c, pointInside) << std::endl;
}

int main() {

  std::cout << "<< Test 1 >>" << std::endl;
  test1();
  std::cout << "\n<< Test 2 >>" << std::endl;
  test2();
  std::cout << "\n<< Test 3 >>" << std::endl;
  test3();
  return 0;
}
