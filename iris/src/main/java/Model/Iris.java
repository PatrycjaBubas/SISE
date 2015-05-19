package Model;

public class Iris {
	@Override
    public String toString() {
        return "Iris{" + "petalLength=" + petalLength + ", petalWidth=" + petalWidth + ", sepalLength=" + sepalLength + ", sepalWidth=" + sepalWidth + ", type=" + type + '}';
    }
    private float petalLength;
    private float petalWidth;
    private float sepalLength;
    private float sepalWidth;
    private String type;

    public float getPetalLength() {
        return petalLength;
    }

    public float getPetalWidth() {
        return petalWidth;
    }

    public float getSepalLength() {
        return sepalLength;
    }

    public float getSepalWidth() {
        return sepalWidth;
    }

    public void setPetalLength(float petalLength) {
        this.petalLength = petalLength;
    }

    public void setPetalWidth(float petalWidth) {
        this.petalWidth = petalWidth;
    }

    public void setSepalLength(float sepalLength) {
        this.sepalLength = sepalLength;
    }

    public void setSepalWidth(float sepalWidth) {
        this.sepalWidth = sepalWidth;
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type the type to set
     */
    public void setType(String type) {
        this.type = type;
    }
}
