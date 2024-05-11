/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:16 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/11 02:08:32 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<iostream>

using namespace std;

int main()

{

string str= "learning at unstop is fun";

cout << str <<'\n';

cout <<" Position of unstop is :";

cout<< str.find("unstopg"); //Match found at index 12.

}