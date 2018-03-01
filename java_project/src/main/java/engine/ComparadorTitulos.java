package engine;
import java.util.Comparator;


public class ComparadorTitulos implements Comparator<String>{
	public int compare (String art1, String art2){
		return (art1.compareTo(art2));
	}
	
}