#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

#include "frame.h"
#include "saveimage.h"

// Idea from https://github.com/sol-prog/Mandelbrot_set and https://github.com/klickers/CppCapstone

// clang++ -std=c++11 -stdlib=libc++ -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage

// Use an alias to simplify the use of complex type
using Complex = std::complex<double>;

// Convert a pixel coordinate to the complex domain
Complex scale(Window<int> &scr, Window<double> &fr, Complex c) {
	Complex aux(c.real() / (double)scr.width() * fr.width() + fr.xMin(),
		c.imag() / (double)scr.height() * fr.height() + fr.yMin());
	return aux;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
int escape(Complex c, int iter_max, const std::function<Complex( Complex, Complex)> &func) {
	Complex z(0);
	int it = 0;

	while (abs(z) < 2.0 && it < iter_max) {
		z = func(z, c);
		it++;
	}

	return it;
}

// Loop over each pixel from our image and check if the points associated with this pixel escape to infinity
void get_number_iterations(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func) {
	int k = 0, progress = -1;
	for(int i = scr.yMin(); i < scr.yMax(); ++i) {
		for(int j = scr.xMin(); j < scr.xMax(); ++j) {
			Complex c((double)j, (double)i);
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			k++;
		}
		if(progress < (int)(i*100.0/scr.yMax())){
			progress = (int)(i*100.0/scr.yMax());
			std::cout << progress << "%\n";
		}
	}
}

void fractal(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func, const char *fname, bool smooth_color) 
{
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

	// Save (show) the result as an image
	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot(int length) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-2.2, 1.2, -1.7, 1.7);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z + c; };

	int iter_max = 400;
	const char *fname = "mandelbrot.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

void mandelbar(int length) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-2.2, 1.2, -1.7, 1.7);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {
      double x = z.real();
      double y = z.imag();
      y *= -1;
      Complex z_bar = (x, y);
      return z_bar * z_bar + c; };

	int iter_max = 400;
	const char *fname = "mandelbar.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

void multibrot(int length) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-1.5, 1.5, -1.5, 1.5);

	// The function used to calculate the fractal
	auto func = [] (Complex z, Complex c) -> Complex {return z * z * z +  c; };

	int iter_max = 500;
	const char *fname = "multibrotp.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}



void multibrotp(int length, Complex k) {
	// Define the size of the image
	Window<int> scr(0, length, 0, length);
	// The domain in which we test for points
	Window<double> fract(-1.5, 1.5, -1.5, 1.5);

	// The function used to calculate the fractal
	auto func = [k] (Complex z, Complex c) -> Complex {return z * z * z + k *  z +  c; };

	int iter_max = 500;
	const char *fname = "multibrot.png";
	bool smooth_color = false;
	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

int main() {

	int length, dim;
	std::string go, smooth, brotbar;
  	Complex k;
  	bool param;

	std::cout << "Hello, Let's generate a squared or cubed Mandelbrot set with given length" << std::endl;
	std::cout << "You will get to decide the type of the Mandelbrot set and its size." << std::endl;
	
	std::cout << "Type 'go' to begin!" << std::endl;
	std::cin >> go;
  	std::cout << "Length of image's side: " << std::endl;
	std::cin >> length;
    std::cout << "Do you want to generate quadratic or cubic Mandelbrot set(enter 2 or 3)?" << std:: endl;
  	std::cin >> dim;
  if (dim == 2){
  std::cout<< "Do you want to generate a mandelbrot or a mandelbar set ?(enter the name):" << std:: endl;
  std::cin >> brotbar;}
  
  if (dim == 3){
  std::cout<< "Do you want to generate a parametrized or nonparametrized multibrot set(1 or 0)?:" << std:: endl;
  std::cin >> param;
  if (param == true){
  std::cout << "Enter a complex number (in (double, double) format):" << std::endl;
  std::cin >> k;
    }
  }
  


	if (dim == 2 && brotbar == "mandelbrot"){
      mandelbrot(length);
    }
  	else if (dim == 2 && brotbar == "mandelbar"){
    mandelbar(length);}
  	else if (dim == 3 && param == false){
	multibrot(length);
    }
	else {
    multibrotp(length, k );}
	std::cout << "The image have been generated!  Check the /build/ folder." << std::endl;

	return 0;
}