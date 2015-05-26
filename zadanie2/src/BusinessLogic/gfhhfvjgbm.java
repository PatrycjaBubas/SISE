import java.util.Collections;

import Model.Iris;
import Model.LearnedIris;

boolean conflict = true;
				int counterSetosa = 0;
				int counterVersicolor = 0;
				int counterVirginica = 0;

				for (Iris oldIris : knownIrisList) {
					LearnedIris newLearnedIris = new LearnedIris();
					newLearnedIris.setNewIris(iris);
					newLearnedIris.setOldIris(oldIris);
					newLearnedIris.setDistance(getDistance(oldIris, iris, m));
					learnedIrises.add(newLearnedIris);
				}
				Collections.sort(learnedIrises);

				while (conflict != false) {
					counterSetosa = 0;
					counterVersicolor = 0;
					counterVirginica = 0;
					for (int i = 0; i < k; i++) {
						type = learnedIrises.get(i).getOldIris().getType();
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
						// zastosowanie standaryzacji (od kazdego argumentu
						// odjac
						// sredni¹ i podzielic przez odchylenie
						conflict = true;
						float mean = 0;
						float s = 0;
						for (int i = 0; i < k; i++) {
							mean += learnedIrises.get(i).getDistance();
						}
						mean /= k;
						// odchylenie
						for (int i = 0; i < k; i++) {
							s += Math.pow(learnedIrises.get(i).getDistance()
									- mean, 2);
						}
						s /= k - 1;
						if (s == 0) {
							s = 0.0001f;
						}
						for (int i = 0; i < k; i++) {
							float d = learnedIrises.get(i).getDistance();
							learnedIrises.get(i).setDistance((d - mean) / s);
						}
						Collections.sort(learnedIrises);
					} else {
						conflict = false;
						break;
					}
				}

				if ((counterSetosa > counterVersicolor)
						&& (counterSetosa > counterVirginica)) {
					type = "Iris-setosa";
				} else if ((counterVersicolor > counterSetosa)
						&& (counterVersicolor > counterVirginica)) {
					type = "Iris-versicolor";
				} else if ((counterVirginica > counterSetosa)
						&& (counterVirginica > counterVersicolor)) {
					type = "Iris-virginica";
				}
				classifiedIris.put(iris, type);
			}