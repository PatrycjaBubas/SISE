package BusinessLogic;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.text.html.HTMLDocument.Iterator;

import Model.Iris;
import Model.LearnedIris;

public class Program {

	public static void main(String[] args) throws IOException {

		// deklaracja zmiennych i list
		String fileIn = null, fileOut = null, fileTest = null, m = null;
		Integer state = -1, k = -1, c = -1;
		Boolean r = false;
		String type = "";
		IrisLoad loader = new IrisLoad();
		List<Iris> knownIrisList = new ArrayList<Iris>();
		List<Iris> testIrisList = new ArrayList<Iris>();
		List<LearnedIris> learnedIrises = new ArrayList<LearnedIris>();
		Map<Iris, String> classifiedIris = new HashMap<Iris, String>();

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
			// za³adowanie plików wejœciowych i wczytanie ich jako obiekty Iris
			// do list learnList i testList
			loader.read(fileIn, fileTest);

			for (Iris iris : loader.getLearnList()) {
				knownIrisList.add(iris);
			}
			for (Iris iris : loader.getQualifyList()) {
				testIrisList.add(iris);
			}
			for (Iris testIris : testIrisList) {
				for (Iris knownIris : knownIrisList) {
					learnedIrises.add(new LearnedIris(testIris, knownIris,
							getDistance(testIris, knownIris, m)));
				}
			}
		} catch (FileNotFoundException fnfE) {
			System.out.println(fnfE);
		}

		List<Integer> typesToWrite = new ArrayList<Integer>();
		for (String irisType : classifiedIris.values()) {
			if (irisType.equals("Iris-setosa")) {
				typesToWrite.add(0);
			} else if (irisType.equals("Iris-versicolor")) {
				typesToWrite.add(1);
			} else if (irisType.equals("Iris-virginica")) {
				typesToWrite.add(2);
			}
		}
		loader.write(typesToWrite, "NewOut.txt");

	}

	/**
	 * Metoda obliczajaca dystans miedzy dwoma obiektami Iris. jesli parametrem
	 * metryki m jest 'CITY', wtedy dystans liczony jest sposobem Manhattan.
	 * Jeœli parametr m jest inny, wtedy dystans liczony jest w sposób
	 * euklidesowski (najkrótsza droga).
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

	public static void standarizeDistances(List<LearnedIris> learnedIrises) {

	}
	
	public void MSE(Map<Iris, String> classifiedIris){
		Integer elem1 = null, elem2 = null, dif = null, mse = null, sum = 0, N = 0;
		Iterator iterator = (Iterator) classifiedIris.keySet().iterator();
		for(Iris elemKey : classifiedIris.keySet()) {
//		    Iris elemValue = classifiedIris.get(elemKey);
		    if(elemKey.getType().equals(classifiedIris.get(elemKey)) == false){
		    	elem1 = Integer.valueOf(elemKey.getType());
		    	elem2 = Integer.valueOf(classifiedIris.get(elemKey));
		    	dif = elem1 - elem2;
		    	sum = sum + dif*dif;
		    	mse=sum/3;
		    	System.out.println("B³¹d œredniokwadratowy nauki:" + mse);
		    }
		}
	}

}
