<h1 align="center">
	📖 get_next_line
</h1>

<p align="center">
	<b><i>Reading a line on a fd is way too tedious</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/jdecorte-be/42-Get-next-line?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/jdecorte-be/42-Get-next-line?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/jdecorte-be/42-Get-next-line?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/jdecorte-be/42-Get-next-line?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/jdecorte-be/42-Get-next-line?color=green" />
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

## Description
This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc.
As a graphic design project, cub3D will enable you to improve your skills in these areas: windows, colors, events, fill shapes, etc.
To conclude cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics.
With the help of the numerous documents available on the internet, you will use
mathematics as a tool to create elegant and efficient algorithms.
![](https://github.com/markveligod/cub3D/raw/master/img/1.png)  

## Bresenham's line algorith  
The Brezenham algorithm is an algorithm that determines which points of a two-dimensional raster need to be colored in order to get a close approximation of a straight line between two specified points.
![](https://github.com/markveligod/cub3D/raw/master/img/2.gif)  
  
The segment is drawn between two points — (x0, y0) and (x1, y1), where these pairs indicate a column and a row, respectively, whose numbers grow to the right and down. First, we will assume that our line goes to the right and down, and the horizontal distance (x1 - x0) exceeds the vertical distance (y1 - y0), that is, the slope of the line from the horizontal is less than 45°. Our goal is to determine for each column x between x0 and x1 which row y is closest to the line and draw a point (x, y).  
General formula for a line between two points:  
`y - y0 = ((y1 - y0) / (x1 - x0)) * (x - x0);`  
Since we know column x, row y is rounded to an integer of the following value:  
`y = ((y1 - y0) / (x1 - x0)) * (x - x0) + y;`  
However, it is not necessary to calculate the exact value of this expression. Suffice it to note that y decreases from y0 and for each step we add one to x and add the slope value to y (in our case, the slope value will be a negative number):  
`s = (y1 - y0) / (x1 - x0);`  
which can be calculated in advance. Moreover, at each step, we do one of two things: either keep the same y, or reduce it by 1.  
You can decide which of these two to choose by tracking the error value, which means the vertical distance between the current y value and the exact y value for the current x. Whenever we increase x, we increase the error value by the slope value s given above. If the error exceeds 1.0, the line gets closer to the next y, so we reduce y by 1.0 while reducing the error value by 1.0. in the implementation of the algorithm below, plot(x,y) draws a point, and abs returns the absolute value of the number:
  
```
function line(int x0, int x1, int y0, int y1)
     int deltax := abs(x1 - x0)
     int deltay := abs(y1 - y0)
     real error := 0
     real deltaerr := (deltay + 1) / (deltax + 1)
     int y := y0
     int diry := y1 - y0
     if diry > 0 
         diry = 1
     if diry < 0 
         diry = -1
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         if error >= 1.0
             y := y + diry
             error := error - 1.0
```
The problem with this approach is that computers work relatively slowly with real variables such as error and deltaerr. In addition, for floating-point calculations, due to restrictions related to the representation of real numbers, it is not possible to get exact values when dividing. This leads to the fact that in the process of computation the accumulation of errors and can lead to undesirable results. For these reasons, it is better to work only with integers. This can be done by multiplying all the real values used by (delta x + 1). Getting the following code:  
```
function line(int x0, int x1, int y0, int y1)
     int deltax := abs(x1 - x0)
     int deltay := abs(y1 - y0)
     int error := 0
     int deltaerr := (deltay + 1)
     int y := y0
     int diry := y1 - y0
     if diry > 0 
         diry = 1
     if diry < 0 
         diry = -1
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         if error >= (deltax + 1)
             y := y + diry
             error := error - (deltax + 1)
```
The need to add one to deltax and deltay is caused by the fact that the function must build a line from a point (x0, y0) to a point (x1, y1) inclusive! Now we can quickly draw right-down lines with a slope value less than 1. It remains to extend the algorithm to drawing in all directions. This is achieved by mirroring, that is, replacing the sign (step 1 is replaced by -1), exchanging variables x and y, and exchanging the coordinates of the beginning of the segment with the coordinates of the end.  
  
There is also Bresenham algorithm to draw circles. The construction method is similar to drawing a line. In this algorithm, the circle arc is constructed for the first quadrant, and the coordinates of the circle points for the remaining quadrants are obtained symmetrically. At each step of the algorithm, three pixels are considered, and the most appropriate one is selected by comparing the distances from the center to the selected pixel with the radius of the circle.
```
// R - radius, X1, Y1 - coordinates of the center
   int x := 0
   int y := R
   int delta := 1 - 2 * R
   int error := 0
   while (y >= 0)
       drawpixel(X1 + x, Y1 + y)
       drawpixel(X1 + x, Y1 - y)
       drawpixel(X1 - x, Y1 + y)
       drawpixel(X1 - x, Y1 - y)
       error = 2 * (delta + y) - 1
       if ((delta < 0) && (error <= 0))
           delta += 2 * ++x + 1
           continue
       if ((delta > 0) && (error > 0))
           delta -= 2 * --y + 1
           continue
       delta += 2 * (++x - --y)
```
![](https://github.com/markveligod/cub3D/raw/master/img/3.gif)  

## DDA algorithm
The DDA-line algorithm rasterizes the line segment between two specified points using calculations in floating-point numbers or integers.  
Let the segment be defined by the real coordinates of the ends (x1, y1), (x2, y2). The raster (integer) coordinates of the endpoints are rounded values of the source coordinates: x_start =round (X1), y_start = round(Y1), x_end = round(x2), and y_end = round(Y2).  

A larger absolute number, (x_end - x_start) or (y_end - y_start), increased by 1 L of the rasterization cycle.  

At the beginning of the cycle the auxiliary real variables x and g are assigned the initial coordinates of the beginning of the segment: x = x1, y = y1. at each step of the loop, these real variables get increments (x_end - x_start) / L, (y_end - y_start) / L. The raster coordinates produced at each step are the result of rounding the corresponding real values x and y.  

The use of calculations with real numbers and only a single use of rounding to finally obtain the value of the raster coordinate results in high accuracy and low performance of the algorithm.  

## Other
[Ray-casting](https://lodev.org/cgtutor/raycasting.html#Textured_Raycaster)  
[Guide MinilibX](https://qst0.github.io/ft_libgfx/man_mlx.html)  
[Guide MinilibX v 2.0](https://harm-smits.github.io/42docs/libs/minilibx)  
  
