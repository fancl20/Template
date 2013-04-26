final class BigFraction extends Number implements Comparable<Number> {
	private static final long serialVersionUID = 2L;
	private final BigInteger numerator,denominator;
	public final BigInteger getNumerator() { return numerator; }
	public final BigInteger getDenominator() { return denominator; }
	public final static BigFraction ZERO = new BigFraction(BigInteger.ZERO, BigInteger.ONE,Reduced.YES);
	public final static BigFraction ONE = new BigFraction(BigInteger.ONE, BigInteger.ONE,Reduced.YES);
	private static enum Reduced {YES,NO};
	public static BigFraction valueOf(Number n) {
		if(n instanceof BigFraction) return (BigFraction)n;
		else return new BigFraction(toBigInteger(n), BigInteger.ONE,Reduced.YES);
	}
	public static BigFraction valueOf(Number numerator, Number denominator) {
		return new BigFraction(toBigInteger(numerator),toBigInteger(denominator),Reduced.NO);
	}
	public static BigFraction valueOf(String s) {
		int slashPos = s.indexOf('/');
		if(slashPos==-1) return valueOf(new BigInteger(s));
		else return valueOf(
				new BigInteger(s.substring(0,slashPos)),
				new BigInteger(s.substring(slashPos+1,s.length())));
	}
	private static BigInteger toBigInteger(Number n) {
		if(n instanceof BigInteger) return (BigInteger)n;
		else return BigInteger.valueOf(n.longValue());
	}
	public BigFraction add(Number n) {
		if(n instanceof BigFraction) {
			BigFraction t = valueOf(n);
			return new BigFraction(
					numerator.multiply(t.denominator).add(denominator.multiply(t.numerator)),
					denominator.multiply(t.denominator),Reduced.NO);
		} else return new BigFraction(
						numerator.add(denominator.multiply(toBigInteger(n))),
						denominator,Reduced.YES);
	}
	public BigFraction substract(Number n) {
		if(n instanceof BigFraction) {
			BigFraction t = valueOf(n);
			return new BigFraction(
					numerator.multiply(t.denominator).subtract(denominator).multiply(t.denominator),
					denominator.multiply(t.denominator),Reduced.NO);
		} else {
			return new BigFraction(
					numerator.subtract(denominator.multiply(toBigInteger(n))),
					denominator,Reduced.YES);
		}
	}
	public BigFraction mutiply(Number n) {
		BigFraction t = valueOf(n);
		return new BigFraction(
				numerator.multiply(t.numerator),
				denominator.multiply(t.denominator),Reduced.NO);
	}
	public BigFraction divide(Number n) {
		BigFraction t = valueOf(n);
		if(t.numerator.equals(BigInteger.ZERO))
			throw new ArithmeticException("Divide by zero");
		return new BigFraction(
				numerator.multiply(t.denominator),
				denominator.multiply(t.numerator),Reduced.NO);
	}
	public BigFraction negate() {
		return new BigFraction(numerator.negate(),denominator,Reduced.YES); 
	}
	public int signum() { return numerator.signum(); }
	@Override
	public String toString() {
		return numerator.toString()+"/"+denominator.toString();
	}
	@Override
	public int hashCode() {
		return (31+numerator.hashCode())*31+denominator.hashCode();
	}
	public int compareTo(Number n) { return this.substract(valueOf(n)).signum(); }
	public Number min(Number n) { return this.compareTo(n)>0?n:this; }
	public Number max(Number n) { return this.compareTo(n)>0?this:n; }
	@Override
	public long longValue() { return 0;}
	public int intValue() { return 0; }
	public short shortValue() { return 0; }
	public double doubleValue() { return 0; }
	public float floatValue() { return 0; }
	private BigFraction(BigInteger numerator,BigInteger denominator,Reduced reduced) {
		if(denominator.equals(BigInteger.ZERO))
			throw new ArithmeticException("Divide by zero: fraction denominator is zero.");
		if(denominator.signum()==-1) {
			numerator = numerator.negate();
			denominator = denominator.negate();
		}
		if(reduced==Reduced.NO) {
			BigInteger gcd = numerator.gcd(denominator);
			numerator = numerator.divide(gcd);
			denominator = denominator.divide(gcd);
		}
		this.numerator = numerator;
		this.denominator = denominator;
	}
}