#!/usr/bin/env python
# coding: utf-8
from abc import ABC, abstractmethod 

# Abstract class to be inherited 
class Polygon(ABC):
    def area(self):
        pass


class Rectangle(Polygon):
    def __init__(self, w, l):
        self.w = w
        self.l = l
    def area(self):
        return self.w * self.l


class Square(Polygon):
    def __init__(self, s):
        self.s = s      
    def area(self):
        return self.s * self.s


class Circle(Polygon):
    def __init__(self, r):
        self.r = r
    def area (self):
        return self.r ** 2 * 3.14


class Triangle(Polygon):
    def __init__(self, b, h):
        self.b = b
        self.h = h
    def area (self):
        return self.b * self.h / 2


class Parallelogram(Polygon):
    def __init__(self, b, h):
        self.b = b
        self.h = h
    def area(self):
        return self.b * self.h


class Trapezoid(Polygon):
    def __init__(self, a, b, h):
        self.a = a
        self.b = b
        self.h = h
    def area(self):
        return (self.a + self.b) * self.h / 2


# Type of print text, make text bold
class color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'


if __name__ == "__main__":
    keys = [1,2,3,4,5,6,7]
    values = ["Rectangle", "Square", "Circle", "Triangle", "Parallelogram", "Trapezoid", "To Exit"]
    # Dictionary Comprehension to generate dictionary with selection & polygon
    myDict = { k:v for (k,v) in zip(keys, values)}   
    
    # List Comprehension to generate list from 1-7
    option = [x for x in range(1,8)]
    
    print("Polygon Area Calculation System")

    # Operator to allow user to start input
    while True:
        for x in option:
            print(str(x) + ". -> " + myDict.get(x))

        try:
            select = int(input("Enter a selection in range 1-7 >>> "))
        except ValueError:
            print ('\nThat\'s not an integer!\n' )
        else:
            if 1 <= select <= 6:  # Selection of Polygon
                if select == 1: 
                    while True: # Define length & width
                        try: 
                            width, length = [float(x) for x in input("Enter Width and Length >>> ").split()]
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if length <= 0 or width <= 0:
                                print("\nLength or Width have to be greater than 0!\n")
                            else:
                                break

                    graph = Rectangle(width, length)
                    print(color.BOLD + "\nThe area of Rectangle: " + str(graph.area()) + color.END + '\n')
                       
                elif select == 2:
                    while True: # Define side
                        try: 
                            side = float(input("Enter a side length >>> "))
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if side <= 0:
                                print("\nSide has to be greater than 0!\n")
                            else:
                                break
                                
                    graph = Square(side)
                    print(color.BOLD + "\nThe area of Square: " + str(graph.area()) + color.END + '\n')
                
                elif select == 3:
                    while True: # Define Radius
                        try: 
                            radius = float(input("Enter a radius >>> "))
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if radius <= 0:
                                print("\nRadius has to be greater than 0!\n")
                            else:
                                break
                                
                    graph = Circle(radius)
                    print(color.BOLD + "\nThe area of Circle: " + str(graph.area()) + color.END + '\n')
                    
                elif select == 4:
                    while True: # Define base & height
                        try: 
                            base, height = [float(x) for x in input("Enter base and height >>> ").split()]
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if base <= 0 or height <= 0:
                                print("\nBase or Height have to be greater than 0!\n")
                            else:
                                break

                    graph = Triangle(base, height)
                    print(color.BOLD + "\nThe area of Triangle: " + str(graph.area()) + color.END + '\n')
                    
                elif select == 5:
                    while True: # Define base & height
                        try: 
                            base, height = [float(x) for x in input("Enter base and height >>> ").split()]
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if base <= 0 or height <= 0:
                                print("\nBase or Height have to be greater than 0!\n")
                            else:
                                break

                    graph = Parallelogram(base, height)
                    print(color.BOLD + "\nThe area of Parallelogram: " + str(graph.area()) + color.END + '\n')
                    
                elif select == 6:
                    while True: # Define two bases and height
                        try: 
                            base1, base2, height = [float(x) for x in input("Enter base1, base2 and height >>> ").split()]
                        except ValueError:
                            print ('\nThat\'s not Valid!\n' )
                        else:
                            if base1 <= 0 or base2 <= 0 or height <= 0:
                                print("\nTwo Bases or Height have to be greater than 0!\n")
                            else:
                                break

                    graph = Trapezoid(base1, base2, height)
                    print(color.BOLD + "\nThe area of Parallelogram: " + str(graph.area()) + color.END + '\n')
     
            elif select == 7:  # Exit the program
                break
            elif select < 1 or select > 7:  # Invalid input
                print('\nOut of range, Try again!\n')

