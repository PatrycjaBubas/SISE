package BusinessLogic;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import com.google.common.collect.*;

import Model.Iris;

public class Program {

	public static void main(String[] args) throws IOException {

		String fileIn = null, fileOut = null, fileTest = null, m = null;
		int state = -1, k = -1, c = -1, rok = -1;
		Boolean r = false;
		IrisLoad loader = new IrisLoad();
		List<Iris> knownIrisList = new ArrayList<Iris>();
		List<Iris> testIrisList = new ArrayList<Iris>();
		ListMultimap<Float, List<Iris>> irisWithDistances = ArrayListMultimap
				.create();

		for (int i = 0; i < args.length; ++i) {
			if (state == 6) {
				c = Integer.valueOf(args[i]);
				state = -1;
			} else if (state == 5) {
				r = Boolean.valueOf(args[i]);
				state = -1;
			} else if (state == 4) {
				m = String.valueOf(args[i]);
				state = -1;
			} else if (state == 3) {
				k = Integer.valueOf(args[i]);
				state = -1;
			} else if (state == 2) {
				fileOut = String.valueOf(args[i]);
				state = -1;
			} else if (state == 1) {
				fileTest = String.valueOf(args[i]);
				state = -1;
			} else if (state == 0) {
				fileIn = String.valueOf(args[i]);
				state = -1;
			} else if (args[i].equals("-c"))
				state = 6;
			else if (args[i].equals("-r"))
				state = 5;
			else if (args[i].equals("-m"))
				state = 4;
			else if (args[i].equals("-k"))
				state = 3;
			else if (args[i].equals("-out"))
				state = 2;
			else if (args[i].equals("-test"))
				state = 1;
			else if (args[i].equals("-in"))
				state = 0;
			else {
				System.out.println("Nieznany parametr");
				return;
			}
		}

		try {
			// za³adowanie plików wejœciowych i wczytanie ich jako obiekty Iris
			// do list learnList i testList
			loader.read(fileIn, fileTest);
			for (Iris iris : loader.getLearnList()) {
				knownIrisList.add(iris);
			}
			for (Iris iris : loader.getQualifyList()) {
				testIrisList.add(iris);
			}

		} catch (FileNotFoundException fnfE) {
			System.out.println(fnfE);
		}

		if (r == true) {

		} else {

		}

		// for (Iris test : testIrisList) {
		// for (Iris known : knownIrisList) {
		// System.out.println(getDistance(known, test, m));
		// List<Iris> irisList = new ArrayList<>();
		// irisList.add(known);
		// irisList.add(test);
		// irisWithDistances.put(getDistance(known, test, m), irisList);
		// }
		// }

	}

	public static float getDistance(Iris oldIris, Iris newIris, String m) {

		float sepalLengthDistance, sepalWidthDistance, sepalDistance, petalLengthDistance, sepalPetalDistance, petalWidthDistance, finalDistance;
		if (m.equals("CITY")) {
			sepalLengthDistance = Math.abs(oldIris.getSepalLength()
					- newIris.getSepalLength());
			sepalWidthDistance = Math.abs(oldIris.getSepalWidth()
					- newIris.getSepalWidth());
			sepalDistance = sepalWidthDistance + sepalLengthDistance;
			petalLengthDistance = Math.abs(oldIris.getPetalLength()
					- newIris.getPetalLength());
			sepalPetalDistance = sepalDistance + petalLengthDistance;
			petalWidthDistance = Math.abs(oldIris.getPetalWidth()
					- newIris.getPetalWidth());
			finalDistance = sepalPetalDistance + petalWidthDistance;
		} else {
			sepalLengthDistance = (float) Math.sqrt(Math.pow(
					oldIris.getSepalLength(), 2)
					+ Math.pow(newIris.getSepalLength(), 2));
			sepalWidthDistance = (float) Math.sqrt(Math.pow(
					oldIris.getSepalWidth(), 2)
					+ Math.pow(newIris.getSepalWidth(), 2));
			sepalDistance = sepalWidthDistance + sepalLengthDistance;
			petalLengthDistance = (float) Math.sqrt(Math.pow(
					oldIris.getPetalLength(), 2)
					+ Math.pow(newIris.getPetalLength(), 2));
			sepalPetalDistance = sepalDistance + petalLengthDistance;
			petalWidthDistance = (float) Math.sqrt(Math.pow(
					oldIris.getPetalWidth(), 2)
					+ Math.pow(newIris.getPetalWidth(), 2));
			finalDistance = sepalPetalDistance + petalWidthDistance;
		}
		return finalDistance;
	}

	public int classify(Iris irisToclassify, List<Iris> knownIrises, int k,
			String m) {
		if (k % 2 == 0) {
			k += 1;
		}
		Multimap<Float, Iris> irisWithDistance = ArrayListMultimap.create();
		List<String> listOfClosestIrises = new ArrayList<String>();
		int counterSetosa = 0;
		int counterVersicolor = 0;
		int counterVirginica = 0;

		for (Iris ir : knownIrises) {
			irisWithDistance.put(getDistance(ir, irisToclassify, m), ir);
		}
		int i = 0;
		for (Iris iris : irisWithDistance.values()) {
			if (i < k) {
				listOfClosestIrises.add(iris.getType());
				i += 1;
			} else {
				break;
			}
		}

		for (String iter : listOfClosestIrises) {
			switch (iter) {
			case "Iris-setosa":
				counterSetosa++;
				break;
			case "Iris-versicolor":
				counterVersicolor++;
				break;
			case "Iris-virginica":
				counterVirginica++;
				break;
			}
		}

		if (counterSetosa > counterVersicolor
				&& counterSetosa > counterVirginica) {
			return 0;
		} else if (counterVersicolor > counterSetosa
				&& counterVersicolor > counterVirginica) {
			return 1;
		} else if (counterVirginica > counterVersicolor
				&& counterVirginica > counterSetosa) {
			return 2;
		} else
			return -1;

	}

}
