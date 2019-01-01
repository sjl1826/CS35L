This homework involved modifying the ray tracer code in a SRT implementation.
I modified the code to make it run multithreaded, speeding up the process.
I modified Makefile to link the -lpthread library.

One of the issues I ran into was using nthreads to loop through
in my output function. I attempted passing nthreads as a second parameter
but instead found an easier solution in declaring nthreads outside of the
function and making it global, modifying its value in main, and then
using it in my output function.

Another issue I ran into was I first received an error because although
I had created my threads correctly, I forgot to call
'pthread_join(threads[t], NULL)'.

When I created my "outputFunction" to pass into pthread_create,
I forgot to return NULL in my function, causing errors.

After running srt, the following was the output:
real  	0m48.200s
user	0m48.202s
sys	0m0.002s

real	0m24.558s
user	0m48.767s
sys	0m0.005s

real	0m12.863s
user	0m51.032s
sys	0m0.002s

real	0m8.148s
user	0m58.149s
sys	0m0.003s

These times were for 1, 2, 4, and 8 threads respectively.
The real time decreases with more threads.

My implementation of SRT improves the performance as we can see that from
1 to 8 threads there was a significant 40 second difference in real time.
However, the overhead of using many threads may limit the speed up
and therefore my implementation wouldn't be perfect because there is
a limit to how much improvement I can achieve.
