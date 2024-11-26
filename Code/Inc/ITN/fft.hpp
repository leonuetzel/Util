#pragma once

#include <ITN/defines.hpp>
#include <ITN/util.hpp>
#include <ITN/complex.hpp>

#include <cmath>





namespace ITN
{
	template<uint32 n>
	class FFT
	{
		public:
			
			
			
			
			
			
			
		private:
			
			Complex<float>* m_x;
			Complex<float>* m_y;
			
			template<uint32 n2>
			Complex<float>* fft(const Complex<float>* x);
			
			void sort(const Complex<float>* y);
			
			
			
			
			
		public:
			
			FFT();
			
			Complex<float>* run(const Complex<float>* x);
	};
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

template<uint32 n>
template<uint32 n2>
ITN::Complex<float>* ITN::FFT<n>::fft(const Complex<float>* x)
{
	//	1-Point FFT doesnt exist
	if(n2 == 1 || n == 1)
	{
		Complex<float>* y = new Complex<float>;
		y[0] = x[0];
		return(y);
	}
	
	
	//	Check if n is Power of 2
	if(std::log2(n) != (uint32) std::log2(n))
	{
		return(nullptr);
	}
	
	
	//	Result Vector
	Complex<float>* y = new Complex<float>[n2];
	
	
	//	Additions
	Complex<float> additions[n2];
	for(uint32 i = 0; i < n2 / 2; i++)
	{
		additions[i]					= x[i] + x[i + n2 / 2];
		additions[i + n2 / 2]	= x[i] - x[i + n2 / 2];
	}
	
	
	//	Multiplications
	struct complexType
	{
		Complex<float> value[n2 / 2];
		
		
		constexpr complexType()
			:	value()
		{
			for(uint32 i = 0; i < n2 / 2; i++)
			{
				float omega = 2 * i * ((float) util::c_pi) / n2;
				value[i] = Complex<float>(std::cos(omega), - std::sin(omega));
			}
		}
		
		constexpr Complex<float> operator[](uint32 index)
		{
			return(value[index]);
		}
	}w;
	
	
	if(n2 > 2)
	{
		Complex<float> multiplications[n2];
		for(uint32 i = 0; i < n2 / 2; i++)
		{
			multiplications[i]					= additions[i];
			multiplications[i + n2 / 2]	= additions[i + n2 / 2] * w[i];
		}
		
		
		//	Create 2 FFTs with Size n2 / 2
		Complex<float>* y0 = fft<n2 / 2>(multiplications);
		Complex<float>* y1 = fft<n2 / 2>(multiplications + n2 / 2);
		
		
		//	Merge Results
		for(uint32 i = 0; i < n2 / 2; i++)
		{
			y[i] = y0[i];
			y[i + n2 / 2] = y1[i];
		}
		delete y0;
		delete y1;
	}
	else
	{
		for(uint32 i = 0; i < n2; i++)
		{
			y[i] = additions[i];
		}
	}
	
	
	//	Return Result
	return(y);
}







template<uint32 n>
void ITN::FFT<n>::sort(const Complex<float>* y)
{
	const uint32 numberOfBits = std::log2(n);
	for(uint32 i = 0; i < n; i++)
	{
		const uint32 mirrored = util::bit::mirror(i) >> (32 - numberOfBits);
		m_y[mirrored] = y[i];
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

template<uint32 n>
ITN::FFT<n>::FFT()
{
	m_x = new Complex<float>[n];
	m_y = new Complex<float>[n];
}


template<uint32 n>
ITN::Complex<float>* ITN::FFT<n>::run(const Complex<float>* x)
{
	//	Check for nullptr
	if(x == nullptr)
	{
		return(nullptr);
	}
	
	
	//	Copy Data
	for(uint32 i = 0; i < n; i++)
	{
		m_x[i] = x[i];
	}
	
	
	//	Clear Output from last Run
	if(m_y == nullptr)
	{
		return(nullptr);
	}
	for(uint32 i = 0; i < n; i++)
	{
		m_y[i] = Complex<float>(0, 0);
	}
	
	
	//	Run
	sort(fft<n>(m_x));
	
	
	//	Return Result
	return(m_y);
}