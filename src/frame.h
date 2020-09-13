#ifndef WINDOW_H
#define WINDOW_H

// source https://github.com/sol-prog/Mandelbrot_set

template <typename T>
class Window {
  	T _xMin, _xMax, _yMin, _yMax;
  	
  	public:
  		Window(T xMin, T xMax, T yMin, T yMax) 
          : _xMin(xMin), _xMax(xMax), _yMin(yMin), _yMax(yMax) {};
  		
  		T size() {
          	return (width() * height());
        }
  		T width() {
          	return (_xMax - _xMin);
        }
  		T height() {
          	return (_yMax - _yMin);
        }
  
  		// Getters and setters for the window elements
        T xMin() const {
            return _xMin;
        }

        void xMin(T xMin) {
            _xMin = xMin;
        }	

        T xMax() const {
            return _xMax;
        }

        void xMax(T _xMax) {
            _xMax = xMax;
        }		

        T yMin() const {
            return _yMin;
        }

        void yMin(T yMin) {
            _yMin = yMin;
        }		

        T yMax() const {
            return _yMax;
        }

        void yMax(T yMax) {
            _yMax = yMax;
        }

    	// Reset all values
        void reset(T xMin, T xMax, T yMin, T yMax) {
            _xMin = xMin;
            _xMax = xMax;
            _yMin = yMin;
            _yMax = yMax;
        }
};


#endif