package engine;

import java.util.TreeMap;
import java.lang.Object;
import java.util.Map;
import java.util.stream.Collectors;

public class Artigo {
    // instance variables - replace the example below with your own
    private long id;
    private long text_size_words;
    private long text_size_bytes;
    private String titulo;
    private TreeMap<Long,Revisao> revisoes;
    
    //Construtor objeto vazio
    public Artigo()
    {
        this.id = 0;
        this.text_size_words = 0;
        this.text_size_bytes = 0;
        this.titulo = "";
        this.revisoes = new TreeMap<Long,Revisao>();
    }
    //Construtor objeto com elementos
    public Artigo(long id, long text_size_words, long text_size_bytes, String titulo, TreeMap<Long,Revisao> revisoes){
        this.id = id;
        this.text_size_words = text_size_words;
        this.text_size_bytes = text_size_bytes;
        this.titulo = titulo;
        setRevisoes(revisoes);
        
}
    public Artigo(Artigo artigo){
        this.id = artigo.getId();
        this.text_size_words = artigo.getTextsizeWords();
        this.text_size_bytes = artigo.getTextsizeBytes();
        this.titulo = artigo.getTitle();
        this.revisoes = new TreeMap<Long,Revisao>();
        this.revisoes.putAll(artigo.getRevisoes());
    }
    
    public long getId(){
        return this.id;
    }
    
    public String getTitle(){
        return this.titulo;
    }
    public long getTextsizeWords(){
        return this.text_size_words;
    }
    public long getTextsizeBytes(){
        return this.text_size_bytes;
    }
    
    public Map<Long,Revisao> getRevisoes (){
        return this.revisoes.entrySet().stream().collect(Collectors.toMap(r->r.getKey(),r->r.getValue().clone()));
    }

    public Revisao getRevisao(long id){
        return this.revisoes.get(id);
    }
    
    public void setId (long id){
        this.id = id;
    }
    
    public void setTitulo(String titulo){
        this.titulo = titulo;
    }
    public void setTextsizeWords(long size){
        this.text_size_words = size;
    }

    public void setTextsizeBytes(long size){
        this.text_size_bytes = size;
    }


    public void setRevisoes(TreeMap<Long,Revisao> r){
        this.revisoes = (TreeMap<Long,Revisao>) r.entrySet().stream().collect(Collectors.toMap(c->c.getKey(),c->c.getValue().clone()));
    }
    
    public Artigo clone(){
        return new Artigo(this);
    }

    public boolean existeRevisao(long id){
        return this.revisoes.containsKey(id);
    }

    public void insereRevisao(Revisao r){
        this.revisoes.put(r.getId(),r);
        }
}
    

    
    
    
    
    
    
    


