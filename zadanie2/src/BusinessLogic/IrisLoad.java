package BusinessLogic;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import Model.Iris;

import com.opencsv.CSVReader;

public class IrisLoad {
	private List<Iris> learnList;
    private List<Iris> qualifyList;

    public void read(String learnFilePath, String testFilePath) throws FileNotFoundException, IOException {

        learnList = new ArrayList<>();
        qualifyList = new ArrayList<>();

        CSVReader learnReader = new CSVReader(new FileReader(learnFilePath), '\t');
        String[] nextLine;
        while ((nextLine = learnReader.readNext()) != null) {
            // nextLine[] is an array of values from the line
            Iris newIris = new Iris();
            newIris.setSepalLength(Float.parseFloat(nextLine[0]));
            newIris.setSepalWidth(Float.parseFloat(nextLine[1]));
            newIris.setPetalLength(Float.parseFloat(nextLine[2]));
            newIris.setPetalWidth(Float.parseFloat(nextLine[3]));
            newIris.setType(nextLine[4]);
            this.learnList.add(newIris);
           // System.out.println(newIris.toString());
        }
        learnReader.close();

        CSVReader testReader = new CSVReader(new FileReader(testFilePath), '\t');
        while ((nextLine = testReader.readNext()) != null) {
            // nextLine[] is an array of values from the line
            Iris newIris = new Iris();
            newIris.setSepalLength(Float.parseFloat(nextLine[0]));
            newIris.setSepalWidth(Float.parseFloat(nextLine[1]));
            newIris.setPetalLength(Float.parseFloat(nextLine[2]));
            newIris.setPetalWidth(Float.parseFloat(nextLine[3]));
            newIris.setType(nextLine[4]);
            this.qualifyList.add(newIris);
           // System.out.println(newIris.toString());
        }
        testReader.close();
    }

	public List<Iris> getLearnList() {
		return learnList;
	}

	public void setLearnList(List<Iris> learnList) {
		this.learnList = learnList;
	}

	public List<Iris> getQualifyList() {
		return qualifyList;
	}

	public void setQualifyList(List<Iris> qualifyList) {
		this.qualifyList = qualifyList;
	}
    
    
}
