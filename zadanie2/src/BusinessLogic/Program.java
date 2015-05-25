package BusinessLogic;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import com.google.common.collect.*;

import Model.Iris;
import Model.LearnedIris;

public class Program {

	public static void main(String[] args) throws IOException {

		// deklaracja zmiennych i list
		String fileIn = null, fileOut = null, fileTest = null, m = null;
		Integer state = -1, k = -1, c = -1;
		Boolean r = false;
		IrisLoad loader = new IrisLoad();
		List<Iris> knownIrisList = new ArrayList<Iris>();
		List<Iris> testIrisList = new ArrayList<Iris>();
		List<LearnedIris> learnedIrises = new ArrayList<LearnedIris>();

		// pobranie argumentow uruchomienia
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
			// za�adowanie plik�w wej�ciowych i wczytanie ich jako obiekty Iris
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

		if (r == false) {
			for (Iris iris : testIrisList) {
				int counterSetosa = 0;
				int counterVersicolor = 0;
				int counterVirginica = 0;
				boolean conflict = false;
				for (Iris oldIris : knownIrisList) {
					LearnedIris newLearnedIris = new LearnedIris();
					newLearnedIris.setNewIris(iris);
					newLearnedIris.setOldIris(oldIris);
					newLearnedIris.setDistance(getDistance(oldIris, iris, m));
					learnedIrises.add(newLearnedIris);
				}
				Collections.sort(learnedIrises);
				for (int i = 0; i < k; i++) {
					String type = learnedIrises.get(i).getOldIris().getType();
					switch (type) {
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

				// sprawdzenie, czy nie nastal konflikt
				if ((counterSetosa == counterVersicolor && counterSetosa != 0)
						|| (counterSetosa == counterVirginica && counterSetosa != 0)
						|| (counterVersicolor == counterVirginica && counterVersicolor != 0)) {

					// rozwi�� konflikt
				}

			}
		} else {

		}

	}

	/**
	 * Metoda obliczajaca dystans miedzy dwoma obiektami Iris. jesli parametrem
	 * metryki m jest 'CITY', wtedy dystans liczony jest sposobem Manhattan.
	 * Je�li parametr m jest inny, wtedy dystans liczony jest w spos�b
	 * euklidesowski (najkr�tsza droga).
	 *
	 * @param oldIris
	 * @param newIris
	 * @param m
	 * @return float dystans
	 */
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

}