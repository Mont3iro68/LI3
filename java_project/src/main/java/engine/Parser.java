package engine;

import java.lang.StringBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

public class Parser {
  public static void parseDoc(ArrayList<String> args, CatalogoArtigos catArtigos, CatalogoContribuidores catContribuidores, int nsnaps) throws FileNotFoundException {
          String[] data = new String[8];
          String text = null;
          String trimmed = null;
          int n = 3;
          int i = 0;
          int contaw = 0;
          long contab = 0;
          long all_art = 0;

          try{
          XMLInputFactory factory = XMLInputFactory.newInstance();
          factory.setProperty("javax.xml.stream.isCoalescing", true);


          for(;i<nsnaps;i++){
          XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(new File(args.get(i))));



      while (reader.hasNext()){
      	int event = reader.next();
      switch(event){
        
        case XMLStreamConstants.END_DOCUMENT:
            reader.close();
            break;

      
        case XMLStreamConstants.CHARACTERS:
            text = reader.getText();
            contab += (long) text.length();
            trimmed = text.trim();
            contaw += trimmed.isEmpty() ? 0 : trimmed.split("\\s+").length;
            
            break;
          
          

        case XMLStreamConstants.END_ELEMENT:
          switch(reader.getLocalName()){

            case "title":
                data[0] = text;
                n = 0;
                break;


            case "id":
                switch (n){
                  case 0:
                      data[1] = text;
                      n++;
                      break;
                  
                  case 1:
                      data[2] = text;
                      break;
                
                  case 2:
                      data[3] = text;
                      break;
                     }
                  break;

            case "timestamp":
                data[4] = text;
              break;
            
            case "username":
                data[5] = text;
                n = 2;
                break;

            case "revision":
            data[6] = "" + contaw;
            data[7] = "" + contab;
            contaw = 0;
            contab = 0;
            insere(data,catArtigos,catContribuidores);
            break;

            case "ip":
            data[3] = "";
            break;

          }
          break;

      }
    }
    reader.close();
  }
}
  catch (XMLStreamException ex){ System.out.println("ERRO");

}

}
 
  public static void insere (String[] data, CatalogoArtigos catArtigos, CatalogoContribuidores catContribuidores){
    long nwords = Long.parseLong(data[6]);
    long nbytes = Long.parseLong(data[7]);
    Revisao revisao = new Revisao(Long.parseLong(data[2]),nwords,nbytes,data[4]);
    Artigo artigo = new Artigo();
    artigo.setId(Long.parseLong(data[1]));
    artigo.setTitulo(data[0]);
    artigo.setTextsizeWords(nwords);
    artigo.setTextsizeBytes(nbytes);

    if(!catArtigos.existeArtigo(artigo.getId())){
      artigo.insereRevisao(revisao);
      catArtigos.insereArtigo(artigo);
      insereCont(data,catContribuidores);
    }
    else{
      artigo = catArtigos.getArtigo(artigo.getId());
      if(!artigo.existeRevisao(revisao.getId())){
        artigo.insereRevisao(revisao);
        insereCont(data,catContribuidores);
        
        if(artigo.getTextsizeWords() < nwords)
          artigo.setTextsizeWords(nwords);
        
        if(artigo.getTextsizeBytes() < nbytes)
          artigo.setTextsizeBytes(nbytes);
        
        if(!artigo.getTitle().equals(data[0]))
          artigo.setTitulo(data[0]);
        

      }
      
      else 
        catArtigos.contaDup();  
  }
    catArtigos.contaAll();
  }         

 

  public static void insereCont(String[] data, CatalogoContribuidores catContribuidores){
     if(!data[3].isEmpty()){
      long id = Long.parseLong(data[3]);

       Contribuidor user = new Contribuidor(id,data[5]);

      if (catContribuidores.existeContribuidor(user.getId())) 
        catContribuidores.getContribuidor(id).addRevisao();
          
      else
        catContribuidores.insereContribuidor(user);
    
    }

  }

}

/* Data[0] = Article Title;
   Data[1] = Article ID;
   Data[2] = Revision ID;
   Data[3] = Contributor ID;
   Data[4] = Revision TimeStamp;
   Data[5] = Contributor Name;
   Data[6] = TextSizeWords;
   Data[7] = TextSizeBytes;
*/