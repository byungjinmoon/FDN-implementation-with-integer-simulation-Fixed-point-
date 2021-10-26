# FDN implementation with integer simulation Fixed point

The floating-point based FDN reverberation was implemented as a fixed-point and ported on the DSP board. (C language)

# Background

### Integer simulation - Fixed point

This method minimize the amount of computation by changing the floating operation to an integer operation.
After integer operation, it is converted to a floating value.

* DSPs Math Formats 
  * Fixed-Point  vs Floating-Point    
  
    <img src="https://user-images.githubusercontent.com/86009768/138582559-e83cd612-4442-46c0-9ea7-2c4a6f399d3b.png" width="500" height="300">
    
* Data Width and Q format 

  Q-format is determined according to the number of bits of the data bus and the specification of the DSP processor. Q-format is partitioned to sign, integer, and fraction part as shown in the figure, and Q-format is determined according to the range of float values to be converted to integer.
  
  <img src="https://user-images.githubusercontent.com/86009768/138582574-924723a7-9a5a-4c5c-817c-d8773b793891.png" width="550" height="200">
  
  * Example of Q 16.15  
    
     <img src="https://user-images.githubusercontent.com/86009768/138582581-96e5239a-2e17-4608-9005-f3a3c5c62ea0.png" width="700" height="400">
  
  * Types of Q format (16bit DATA)
  
    <img src="https://user-images.githubusercontent.com/86009768/138582596-97001c76-0419-4f10-b95b-022b2724225d.png" width="700" height="400">


* Q Format Addition
  * Considerations
    * Need to align radix points 
    * Overflow protection
    * Example) 0.75 + 0.5 = 1.25
    
      ![image](https://user-images.githubusercontent.com/86009768/138582614-c6057067-c0c5-4c8d-9d5b-c6c3f057b309.png)

* Q Format Multiplication
  * Considerations
    * Difference between integer and fixed-point multiplication
    
      ![image](https://user-images.githubusercontent.com/86009768/138582658-cb6bef15-53cb-4d18-b2b2-867aafb726a9.png)

# Experimental results

* Integer simulation of FDN reverberation using Q-format
  * Set Q-format of the Input, output, coefficients…
    ![image](https://user-images.githubusercontent.com/86009768/138683890-1501c29d-3b5b-46c2-9c68-164607cffc53.png)

* Integer simulation steps
  ![image](https://user-images.githubusercontent.com/86009768/138686439-4cbf02c5-90fc-49ad-a2e1-82f1a6c18cd0.png)
  
  *__Rounding example__
    
    When Q32.31 is obtained as a result of FIR or IIR filtering of Q16.15, round calculation is performed by adding 0x8000 before truncation of the necessary preceding 16 bits.
    
    ![image](https://user-images.githubusercontent.com/86009768/138687701-06e91c68-d3c8-4aad-95a4-11b66c2860ea.png)

* Exepriments and Results
  * Frequency dependent FDN using __FIR__ filtering 
    * Precision of integer simulation
      * Difference between Floating and Fixed Point
       
        The figure shows the difference between floating point and fixed point simulation results, and a difference of about 10 to 15 (4 bits) occurs.

        ![image](https://user-images.githubusercontent.com/86009768/138690984-88f029b1-a9f7-4b4b-988c-df79c20356ea.png)
   
   * Frequency dependent FDN using __IIR__ filtering 
     * Design IIR filter and set Q-format
       ![image](https://user-images.githubusercontent.com/86009768/138691129-c9451ea5-9bba-4808-aac7-55d99307186e.png)
     
     * Precision of integer simulation
       * Difference between Floating and Fixed Point
         
         The figure shows the difference between floating point and fixed point simulation results, and a difference of about 2 to 4 (2 bits) occurs.

         ![image](https://user-images.githubusercontent.com/86009768/138691421-cd28067d-0802-412e-9c11-759467a6a685.png)

  
  * Ported on DSP board
    ![image](https://user-images.githubusercontent.com/86009768/138691676-2f3707f0-24e8-414e-8b20-b4f50a7befbf.png)

