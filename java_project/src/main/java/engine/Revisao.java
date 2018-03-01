package engine;

public class Revisao{
    private long id;
    private long text_size_words;
    private long text_size_bytes;
    private String time_stamp;
   

    public Revisao(){
        this.id = 0;
        this.text_size_words = 0;
        this.text_size_bytes = 0;
        this.time_stamp = "";
    }

    public Revisao(long id, long text_size_words, long text_size_bytes, String time_stamp){
        this.id = id;
        this.text_size_words = text_size_words;
        this.text_size_bytes = text_size_bytes;
        this.time_stamp = time_stamp;
    }

    public Revisao(Revisao revisao){
        this.id = revisao.getId();
        this.text_size_words = revisao.getTextSizeWords();
        this.text_size_bytes = revisao.getTextSizeBytes();
        this.time_stamp = revisao.getTimeStamp();
    }

    //Get's
    public long getId(){
        return this.id;
    }

    public long getTextSizeWords(){
        return this.text_size_words;
    }

    public long getTextSizeBytes(){
        return this.text_size_bytes;
    }

    public String getTimeStamp(){
        return this.time_stamp;
    }

    //Set's
    public void setId(long id){
        this.id = id;
    }

    public void setTextSizeWords(long text_size_words){
        this.text_size_words = text_size_words;
    }

    public void setTextSizeBytes(long text_size_bytes){
        this.text_size_bytes = text_size_bytes;
    }

    public void setTimeStamp(String time_stamp){
        this.time_stamp = time_stamp;
    }

    
    
    public Revisao clone(){
        return new Revisao (this);
    }
}