package engine;
import java.util.Comparator;
import java.util.Map;

public class ComparadorContribuidores implements Comparator<Map.Entry<Long,Contribuidor>> {
	public int compare (Map.Entry<Long, Contribuidor> map1, Map.Entry<Long, Contribuidor> map2) {
		long m1 = (map1.getValue().getNumRevisoes()) - (map2.getValue().getNumRevisoes());
		if (m1>0) return -1;
		if (m1<0) return 1;
		return (map1.getKey().compareTo(map2.getKey()));
		
	}	
}
