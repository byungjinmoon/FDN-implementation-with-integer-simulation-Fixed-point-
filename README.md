# FDN implementation with integer simulation Fixed point

The floating-point based FDN reverberation was implemented as a fixed-point and ported on the DSP board. (C language)

# Background

### Integer simulation - Fixed point

This method minimize the amount of computation by changing the floating operation to an integer operation.
After integer operation, it is converted to a floating value.

* DSPs Math Formats 
  * Fixed-Point  vs Floating-Point
    ![image](https://user-images.githubusercontent.com/86009768/138582559-e83cd612-4442-46c0-9ea7-2c4a6f399d3b.png)
    
* Data Width and Q format 

  Q-format is determined according to the number of bits of the data bus and the specification of the DSP processor. Q-format is partitioned to sign, integer, and fraction part as shown in the figure, and Q-format is determined according to the range of float values to be converted to integer.

  ![image](https://user-images.githubusercontent.com/86009768/138582574-924723a7-9a5a-4c5c-817c-d8773b793891.png)
  
  * Example of Q 16.15  
    
    ![image](https://user-images.githubusercontent.com/86009768/138582581-96e5239a-2e17-4608-9005-f3a3c5c62ea0.png)
  
  * Types of Q format (16bit DATA)
  
    ![image](https://user-images.githubusercontent.com/86009768/138582596-97001c76-0419-4f10-b95b-022b2724225d.png)


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


