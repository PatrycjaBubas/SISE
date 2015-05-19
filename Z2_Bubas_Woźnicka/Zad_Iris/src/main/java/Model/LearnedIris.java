package Model;

import java.util.List;
import com.google.common.collect.Multimap;

public class LearnedIris {
	Iris oldIris;
	Iris newIris;
	Multimap<Float, Iris> distances;

	public LearnedIris(Iris iirisNew, List<Iris> iirisOldList) {
		this.newIris = iirisNew;
		for (Iris iiris : iirisOldList) {
			distances.put(getDistance(iiris, iirisNew), iiris);
		}
	}

	@Override
	public String toString() {
		return "LearnedIris [oldIris=" + oldIris + ", newIris=" + newIris
				+ ", distances=" + distances + "]";
	}

	public float getDistance(Iris oldIris, Iris newIris) {

		float sepalLengthDistance = Math.abs(oldIris.getSepalLength()
				- newIris.getSepalLength());
		float sepalWidthDistance = Math.abs(oldIris.getSepalWidth()
				- newIris.getSepalWidth());
		float sepalDistance = sepalWidthDistance + sepalLengthDistance;
		float petalLengthDistance = Math.abs(oldIris.getPetalLength()
				- newIris.getPetalLength());
		float sepalPetalDistance = sepalDistance + petalLengthDistance;
		float petalWidthDistance = Math.abs(oldIris.getPetalWidth()
				- newIris.getPetalWidth());
		float finalDistance = sepalPetalDistance + petalWidthDistance;
		return finalDistance;
	}
}
