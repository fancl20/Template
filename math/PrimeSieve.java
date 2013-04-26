class PrimeSieve {
	public static void getIsPrime(boolean isPrime[]) {
		for(int i=2;i<=isPrime.length;++i) isPrime[i] = true;
		for(int i=2;i*i<=isPrime.length;++i) if(isPrime[i])
			for(int j = i;i*j<=isPrime.length;++j)
				isPrime[i*j] = false;
	}
	public static int getPrimeList(boolean isPrime[],int primeList[]) {
		int size = 0;
		for(int i=2;i!=isPrime.length;++i) if(isPrime[i])
			primeList[size++] = i;
		return size;
	}
}