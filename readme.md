# Dining philosophers PoC

Proste rozwiązanie problemu z użyciem biblioteki <atomic>.
Rozwiązanie posiada race conditions.
```c++
void hungry(int id)
{
	states[id].store(1);
	int l = id - 1 >= 0 ? id - 1 : NUM_THREADS - 1;
	int r = (id + 1) % NUM_THREADS;

	while (states[l].load() == 2 || states[r].load() == 2)
	{
		;
	}
}
```
Dwa sąsiednie wątki mogą wyjść z pętli while, gdy zostaną spełnione szczególne warunki.