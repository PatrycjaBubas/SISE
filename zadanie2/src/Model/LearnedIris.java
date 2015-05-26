package Model;

public class LearnedIris implements Comparable<LearnedIris> {

	private Iris newIris;
	private Iris oldIris;
	private float distance;

	public LearnedIris(Iris newIris, Iris oldIris, float distance) {
		super();
		this.newIris = newIris;
		this.oldIris = oldIris;
		this.distance = distance;
	}

	public Iris getNewIris() {
		return newIris;
	}

	public void setNewIris(Iris newIris) {
		this.newIris = newIris;
	}

	public Iris getOldIris() {
		return oldIris;
	}

	public void setOldIris(Iris oldIris) {
		this.oldIris = oldIris;
	}

	public float getDistance() {
		return distance;
	}

	public void setDistance(float distance) {
		this.distance = distance;
	}

	@Override
	public int compareTo(LearnedIris o) {
		int result = Float.compare(this.getDistance(), o.getDistance());
		return result;
	}
}
