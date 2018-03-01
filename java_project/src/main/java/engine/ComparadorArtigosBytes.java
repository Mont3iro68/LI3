package engine;
import java.util.Comparator;
import java.util.Map;

public class ComparadorArtigosBytes implements Comparator<Map.Entry<Long,Artigo>> {
	public int compare (Map.Entry<Long, Artigo> map1, Map.Entry<Long, Artigo> map2) {
		long m1 = (map1.getValue().getTextsizeBytes() - (map2.getValue().getTextsizeBytes()));
		if (m1>0) return -1;
		if (m1<0) return 1;
		return (map1.getKey().compareTo(map2.getKey()));
		
	}	
}
