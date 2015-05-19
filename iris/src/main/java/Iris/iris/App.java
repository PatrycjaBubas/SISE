package Iris.iris;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import Model.Iris;
import Model.LearnedIris;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args ) throws IOException{
    	IrisLoad loader = new IrisLoad();
		List<Iris> knownIrisList = new ArrayList<Iris>();
		List<Iris> testIrisList = new ArrayList<Iris>();
		List<LearnedIris> irisWithDistances = new ArrayList<LearnedIris>();
		try {
			// załadowanie plików wejściowych i wczytanie ich jako obiekty Iris
			// do list learnList i testList
			loader.read("Learn.csv", "Test.csv");
			for(Iris iris : loader.learnList){
				knownIrisList.add(iris);
			}
			for(Iris iris : loader.qualifyList){
				testIrisList.add(iris);
			}
			
			System.out.println(loader.learnList.size());

		} catch (FileNotFoundException fnfE) {
			System.out.println(fnfE);
		}
    }
}
