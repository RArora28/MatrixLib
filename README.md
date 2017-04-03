## **Matrix Library** 
### (Implemented the following as the competency test for **Boost.uBLAS** Gsoc '17)


It uses **C++** features:
 * Expression Templates
 * Move Constructor and Move assignment operators (C++ 11 onwards)
 
Files: 
  * **matrix.hpp**: Normal implementation using class templates and move semantics.
  * **matrixv2.hpp**: Expression evalutated by constructing an expression template.
  
Highlights:
  * **Expression Templates**: Reduce the run time substantially by creating expression templates and avoiding temporary memory allocation and virtual function calls
  * **Generic Lambdas**: unnamed functions used instead of functions
  * **Move Semantics**: Move assignment and Move constructor (matrix.hpp) used which move the rhs value directly to the destination avoiding costly deepcopy 

### Functions Supported :
  1. #### **Create Matrices** :
     ```Matrix <Type_of_elements> Object_Name(parameters)```
     * Parameters: 
        * Empty: Intialises an empty Matrix of dimensions 0 X 0 
        * row, column: Intialises an empty matrix with dimensions row X column 
        * Another_Matrix_Object: copy's the contents of Another_Matrix_Object to Object_Name
        * A rhs value of type Matrix: moves the contents of the rhs Matrix to Object_Name
     * Type_of_elements: All numeric types supported (eg: int, double, float, complex<long long> etc.)
  
  1. #### **Accessing and Modifying Matrix Elements** :
     * ```ObjectName.setVal(row, column, some_val)```: Sets the value "matrix[row][column]" to some_val.
     * ```ObjectName.getVal(row, column)```: Returns the value "matrix[row][column]"

  1. #### **Matrix addition/subtraction/multiplication** :
     (M1, M2, M3 are the objects of the Matrix class)
     * ```M1 = M2 +/-/* M3```          (stores the result of M2 + M3 in M1)
     * ```M1 +/-/*= M2```             (Adds M2 to M1)  
                
  1. #### **Negation operator (-)** :
     * ```A = -B``` (stores the result of multiplying the -1 to matrix B into A
            
  1. #### **Complex combinations of above operations** :
     * ```A += (C - D) * (B + E + F + (G * H) )```
            
  1. #### **Move Assignment** (if rhs value)  and **Copy Assignment** (if lhs value)
  
### How to use this header: 
  1. Clone/Download this directory (or the file "matrix.hpp")
  1. Include the header in your code by specifying the absolute or relative path **( #include"/file_path/matrix.hpp")**
