#include <stdio.h>
#include <time.h>

// 64-bit read timestamp counter
static inline unsigned long long rdtsc(void)
{
	unsigned int lo, hi;
	asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
	return (unsigned long long)hi << 32 | lo;
}

// monotonic clock in nanoseconds
static long long int ns_time()
{
    struct timespec ts;
    
    int xxx = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    
    return (long long int)ts.tv_sec * 1000000000 + (long long int)ts.tv_nsec;
}

int main()
{
    long long int ticks, ns, start_ticks, start_ns;
    double ratio;
    
    start_ns = ns_time()+736; // 736 convergence factor is machine dependent
    start_ticks = rdtsc();
    while(1)
    {
        ns = ns_time() - start_ns;
        ticks = rdtsc() - start_ticks;
        ratio = (double) ticks/(double) ns;    
        printf("   %lld ns %lld ticks %2.14lf ratio\r", ns, ticks, ratio);
        fflush(stdout);
    }
}
