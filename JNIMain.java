public class JNIMain {

	private static String defaultDll = "jnimain";

	private static String getDllFileName(String[] args) {
		return args.length == 0 ? defaultDll : args[0];
	}

	private static void loadDll(String dllFileName) {
		try {
			System.loadLibrary(dllFileName);
		}
		catch (NullPointerException ex) {
			//System.out.println("error: dll-file not specified");
		}
		catch (UnsatisfiedLinkError ex) {
			System.out.println("error: \"" + dllFileName + "\" not found");
		}
	}

	private int numberField = 11;

	private String secretMessageField = "Aliens will attack at...";

	private static double numberStaticField = 35;

	private static String messageStaticField = "Our hearts stand strong";

	private void callback() {
		System.out.println("In Java | instance CALLBACK");
	}

	private int callback(int a, int b) {
		return a < b ? a : b;
	}

	private static void callbackStatic() {
		System.out.println("In Java | static CALLBACK");
	}

	private static String callbackStatic(String line) {
		return "|" + line + "|";
	}

	private native void sayHelloToC();

	private native double average(int a, int b);

	private native String reverse(String line);

	private native double median(double[] arr);

	private native void modifyFields();

	private native void modifyStaticFields();

	private native void useCallback();

	private native void useStaticCallback();

	private native Integer convertToIntegerObject(int number);

	private native double convertToDoublePrimitive(Double number);

	private native Double[] getSumAndAverage(Integer[] numbers);

	public static void main(String[] args) {
		loadDll(getDllFileName(args));

		JNIMain inst = new JNIMain();

		inst.sayHelloToC();
		System.out.println("average = " + inst.average(1, 2));
		System.out.println("live reversed = " + inst.reverse("live"));
		System.out.println("median = " + inst.median(new double[]{1, 6, 7, 3, 4, 2, 5}));
		
		inst.modifyFields();
		System.out.println("Instance values: " + inst.numberField + " | " + inst.secretMessageField);
	}
}