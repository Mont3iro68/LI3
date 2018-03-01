package engine;

import java.util.TreeMap;
import java.lang.Object;
import java.util.Map;
import java.util.stream.Collectors;

public class CatalogoArtigos {
    private TreeMap<Long,Artigo> catArtigos;
    private long dup;
    private long all;
    
    public CatalogoArtigos(){
        this.catArtigos = new TreeMap<Long,Artigo>();
        this.dup = 0;
        this.all = 0;
    }

    public CatalogoArtigos(TreeMap<Long,Artigo> cat, long d, long a){
        setCatalago(cat);
        this.dup = d;
        this.all = a;
    }
    
    public CatalogoArtigos(CatalogoArtigos cat){
        this.catArtigos = new TreeMap<Long,Artigo>(); 
        catArtigos.putAll(cat.getCatalogoArtigos());
        this.dup = cat.getDup();
        this.all = cat.getAll();

    }
    
    public Map<Long,Artigo> getCatalogoArtigos (){
        return this.catArtigos.entrySet().stream().collect(Collectors.toMap(e->e.getKey(),e->e.getValue().clone()));
    }

    public long getDup(){
        return this.dup;
    }
    
    public Artigo getArtigo(long id){
        return this.catArtigos.get(id);
    }

    public long getAll(){
        return this.all;
    }

    public void setCatalago(TreeMap<Long,Artigo> cat) {
        this.catArtigos = (TreeMap<Long,Artigo>) cat.entrySet().stream().collect(Collectors.toMap(c->c.getKey(),c->c.getValue().clone()));
    }
    
    public void insereArtigo(Artigo a){
        this.catArtigos.put(a.getId(),a);
    }

    public void contaDup(){
        this.dup ++;
    }


    public void contaAll(){
        this.all ++;
    }

    public long tamCatArtigos(){
        return (long) this.catArtigos.size();
    }

    public boolean existeArtigo(long id){
        return this.catArtigos.containsKey(id);
    }


}
