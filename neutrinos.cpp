/*
** EPITECH PROJECT, 2020
** IQ
** File description:
** IQ.cpp
*/

#include "neutrinos.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <time.h>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

bool parseNumber(const std::string &s)
{
    for (size_t i = 0; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
    }
    return true;
}

int parseArgs(char **args, Datas &datas)
{
    std::string s1(args[1]);
    std::string s2(args[2]);
    std::string s3(args[3]);
    std::string s4(args[4]);

    if (!parseNumber(s1))
        return MY_ERROR;
    if (!parseNumber(s2))
        return MY_ERROR;
    if (!parseNumber(s3))
        return MY_ERROR;
    if (!parseNumber(s4))
        return MY_ERROR;
    datas.n = std::stod(s1);
    datas.a = std::stod(s2);
    datas.h = std::stod(s3);
    datas.sd = std::stod(s4);
    if (datas.n == 0 || datas.h == 0) {
        return MY_ERROR;
    }
    return MY_SUCCESS;
}

bool parseValue(const std::string &str, double &value)
{
    if (!parseNumber(str))
        return false;
    value = std::stod(str);
    return true;
}

int interpretor(Datas &datas)
{
    std::string command;
    double value = 0;
    double comp = 0;
    double square = 0;
    double root = 0;

    std::cout << "Enter next value: ";
    for (std::getline(std::cin, command); command != "END" && command != ""; std::getline(std::cin, command)) {
        if (!parseValue(command, value)) {
            std::cerr << "Wrong value." << std::endl;
            return MY_ERROR;
        }
        else {
            comp = datas.a * datas.n;
            square = (std::pow(datas.sd, 2) + std::pow(datas.a, 2)) * datas.n;
            datas.n++;
            datas.a = (comp + value) / datas.n;
            std::cout << std::fixed << std::setprecision(0);
            std::cout << "    Number of values:\t" << datas.n << std::endl;
            std::cout << std::fixed << std::setprecision(2);
            datas.sd = std::sqrt(((square + std::pow(value, 2)) / datas.n) - std::pow(datas.a, 2));
            std::cout << "    Standard deviation:\t" << datas.sd << std::endl;
            std::cout << "    Arithmetic mean:\t" << datas.a << std::endl;
            root = std::sqrt((square + std::pow(value, 2)) / datas.n);
            std::cout << "    Root mean square:\t" << root << std::endl;
            datas.h = datas.n / ((1 / value) + ((datas.n - 1) / datas.h));
            std::cout << "    Harmonic mean:\t" << datas.h << std::endl << std::endl;
        }
        std::cout << "Enter next value: ";
    }
    return MY_SUCCESS;
}

int neutrinos(int ac, char **args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac == 2) {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
        else
            return MY_ERROR;
    }
    else if (ac == 5) {
        if (parseArgs(args, datas) == MY_ERROR)
            return MY_ERROR;
        else {
            return interpretor(datas);
        }
    }
    else
        result = MY_ERROR;
    return result;
}