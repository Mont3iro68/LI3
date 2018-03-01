package engine;

import java.util.TreeMap;
import java.lang.Object;
import java.util.Map;
import java.util.stream.Collectors;

public class CatalogoContribuidores {
    private TreeMap<Long,Contribuidor> catContribuidores;
    
    public CatalogoContribuidores(){
        this.catContribuidores = new TreeMap<Long,Contribuidor>();
    }

    public CatalogoContribuidores(TreeMap<Long,Contribuidor> cat){
        setCatalago(cat);
    }
    
    public CatalogoContribuidores (CatalogoContribuidores cat) {
        this.catContribuidores = (TreeMap<Long,Contribuidor>) cat.getContribuidores();
    
    }
     
    public Map<Long,Contribuidor> getContribuidores(){
        return this.catContribuidores.entrySet().stream().collect(Collectors.toMap(c->c.getKey(),c->c.getValue().clone()));
    }
    
    public void setCatalago(TreeMap<Long,Contribuidor> cat) {
        this.catContribuidores = (TreeMap<Long,Contribuidor>) cat.entrySet().stream().collect(Collectors.toMap(c->c.getKey(),c->c.getValue().clone()));
    }

    public void insereContribuidor(Contribuidor c){
        this.catContribuidores.put(c.getId(),c);
    }

    public Contribuidor getContribuidor(long id){
        return this.catContribuidores.get(id);
    } 
    public boolean existeContribuidor (long id){
        return this.catContribuidores.containsKey(id);
    }
}    


