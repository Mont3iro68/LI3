package engine;

import li3.Interface;
import engine.Parser;
import java.util.ArrayList;
import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.util.stream.Collectors;
import java.util.Map;
import java.util.TreeMap;
import java.util.Comparator;


public class QueryEngineImpl implements Interface {

    private CatalogoArtigos catArtigos;
    private CatalogoContribuidores catContribuidores;

    public void init() {
       this.catArtigos = new CatalogoArtigos();
       this.catContribuidores = new CatalogoContribuidores();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths){
        try{
        Parser.parseDoc(snaps_paths,this.catArtigos,this.catContribuidores,nsnaps);
    }
        catch(FileNotFoundException ex){
            System.out.println("ERRO! Ficheiro nao encontrado");
        }
    }

    

    public long all_articles() {
        return this.catArtigos.getAll();
    }

    public long unique_articles() {
        return (long) this.catArtigos.tamCatArtigos();
    }

    public long all_revisions() {
        return  (this.catArtigos.getAll() - this.catArtigos.getDup());
    }

    public ArrayList<Long> top_10_contributors() {
        Comparator<Map.Entry<Long,Contribuidor>> comparadorNrevisoes = new ComparadorContribuidores();
        return this.catContribuidores.getContribuidores().entrySet().stream().sorted(comparadorNrevisoes)
        .limit(10)
        .map(e->e.getValue().getId())
        .collect(Collectors.toCollection(ArrayList :: new));
    }

    public String contributor_name(long contributor_id) {

        return this.catContribuidores.getContribuidor(contributor_id).getNome();
    }

    public ArrayList<Long> top_20_largest_articles() {
        Comparator<Map.Entry<Long,Artigo>> comparadorArtigos_bytes = new ComparadorArtigosBytes();
        return this.catArtigos.getCatalogoArtigos().entrySet().stream().sorted(comparadorArtigos_bytes)
        .limit(20)
        .map(e->e.getKey())
        .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_title(long article_id) {

        return this.catArtigos.getArtigo(article_id).getTitle();
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {
        Comparator<Map.Entry<Long,Artigo>> comparadorArtigos_words = new ComparadorArtigosWords();
        return this.catArtigos.getCatalogoArtigos().entrySet().stream().sorted(comparadorArtigos_words).limit(n).map(e->e.getKey())
        .collect(Collectors.toCollection(ArrayList :: new));
    }

    public ArrayList<String> titles_with_prefix(String prefix) {
        Comparator<String> comparadorTitulos = new ComparadorTitulos();
        return this.catArtigos.getCatalogoArtigos().values().stream().map(a->a.getTitle()).filter(s->s.startsWith(prefix)).sorted(comparadorTitulos).collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_timestamp(long article_id, long revision_id) {

        return this.catArtigos.getArtigo(article_id).getRevisao(revision_id).getTimeStamp();
    }

    public void clean() {

    }
}
