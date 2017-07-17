#ifndef TIME_MEASURE_H_INCLUDED
#define TIME_MEASURE_H_INCLUDED

#include "library.h"
#include <chrono>


// Example use below
// ----------------------------------------------------------------------------

//	cout << measure < chrono::nanoseconds>::execution( [&dummy]()
//	{
//		dummy *= 2; // usage with lambdas
//		cout << "In lambda, run for ";
//		usleep(33);

//	}) << endl;

// ----------------------------------------------------------------------------

//	std::cout << measure<std::chrono::nanoseconds>::execution(functor(dummy)) << std::endl;

//	std::cout << measure<std::chrono::nanoseconds>::execution(func);

// ----------------------------------------------------------------------------

// TYPE of chrono::
/*

duration
hours
minutes
seconds
milliseconds
microseconds

*/
// ----------------------------------------------------------------------------
 using namespace std::chrono;


template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F&& func, Args&&... args)
    {
        auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT>
                            (std::chrono::steady_clock::now() - start);
        return duration.count();
    }
};
// ----------------------------------------------------------------------------
struct functor
{
	int state;
	functor(int state) : state(state) {}
	void operator()() const
	{
		std::cout << "In functor run for ";
	}
};

void func()
{
	std::cout << "In function, run for ";sleep(1);
}
/*

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    // Using time point and system_clock
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

*/
// ----------------------------------------------------------------------------
#endif // TIME_MEASURE_H_INCLUDED
