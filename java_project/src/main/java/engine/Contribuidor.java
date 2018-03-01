package engine;


public class Contribuidor{
    private long id;
    private String nome;
    private long numRevisoes;

    public Contribuidor(){
        this.id = 0;
        this.nome = "";
        this.numRevisoes = 0;
    }
    
    public Contribuidor(long id, String nome){
        this.id = id;
        this.nome = nome;
        this.numRevisoes = 1;
    }
    
    public Contribuidor(Contribuidor contribuidor){
        this.id = contribuidor.getId();
        this.nome = contribuidor.getNome();
        setNumRevisoes(contribuidor.getNumRevisoes());
    }
    
    
    public long getId(){
        return this.id;
    }
    
    public String getNome(){
        return this.nome;
    }
    
    public long getNumRevisoes(){
        return this.numRevisoes;
    }
    
    public void setId(long id){
        this.id = id;
    }
    
    public void setNome(String nome){
        this.nome = nome;
    }
    
    public void setNumRevisoes(long numRevisoes){
        this.numRevisoes = numRevisoes;  
    }

    public void addRevisao(){
        this.numRevisoes ++;
    }


    public Contribuidor clone(){
        return new Contribuidor (this);
    }
}