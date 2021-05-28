# Big Integers
Esta biblioteca fornece a possibilidade de realizar operações matemáticas com números acima de 32 bits na linguagem C.

# Exemplo
Neste código é realizado a operação 9999^500

```sh
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bn.h"

int main(){
  
  BIGNUM *base      = int_to_bn(9999);
  BIGNUM *expoente  = int_to_bn(500);
  BIGNUM *resultado = init_bn();
  
  pow_bn(base, expoente, resultado);
  println_bn(resultado);
  
  free_bn(base);
  free_bn(expoente);
  free_bn(resultado);
 
  return 0;
}
```
Resultado

```sh
+95122704627157561443294812328344788384965859010735775319935530454704255762401717865250788831647825358680452758817585887525507213451074546668883588225853340400677512814490114072551779908058229418251051333376924031130836752574060854717773311349685072025595954304899554866458296619988311471515924269914341495519671564383280600862677720589851446928994777178776229992752999048865690512725749471736851099214756768319883835096125949534863389654935590136977828853059549057386080497380286735099245023875235023337335242795645644170264404340631889798525116138622019867179787549828163248551663616392073890686682652212118890354052519824690001617333717421968208177399432067218074277055415984332881291719020810123058932614653864496225822543602421238804387928185512472444743663879768324543840850508431186558775439878126741006913407612271785293996225320095015172040990138769645476784234075206795969096889514782617750163712382947247168618335227764334915564235064422849023816253413536332237833138855861566298394878145012295688541076587434404027150858216834900920191212905147773246412521749074005365306947354008232207957022570811414684023601215741529374847095469718655094177834029379601083100513214853689680067028925072973167138862749622255796375476575991557637912702234309351104599227533777505206981489894148206341612554427174962092079802466655645102064726006484211568142101542936698719073438829939833783651227336656413697322011814009662198220765668180569367895954377735119046801008951923142535369200002550259808594415561658039038611906923600874197883412726816303729733612475738624463402173502673348247206350564835492551625565511436519698689136186842015662846515819183931975769327725725245182685592156793046762391333642870556859152167474236079117407852891673154126971648457476528807305550788754548078582477682800415616397869842856656048617984671316530623762512496200610760793071514211988640738834506879575047495347428169162689589675963023762690198588960583063855679120649131371833858985321202556970290541512474995000001
```

OBSERVAÇÃO: Esta biblioteca é apenas para fins de estudo. A complexidade dos algoritmos implementados não é ideal para ser usada em casos reais. Utilize está biblioteca apenas como uma fonte de informação sobre como se pode trabalhar com números acima de 32bits. 
