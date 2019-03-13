//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

   static const boost::array<boost::array<typename table_type<T>::type, 3>, 150> erf_small_data = { {
      {{ SC_(0.0), SC_(0.0), SC_(1.0) }}, 
      {{ SC_(0.140129846432481707092372958328991613128e-44), SC_(0.1581195994027057927040695988659415347357e-44), SC_(1.0) }}, 
      {{ SC_(0.2802596928649634141847459166579832262561e-44), SC_(0.3162391988054115854081391977318830694715e-44), SC_(1.0) }}, 
      {{ SC_(0.4203895392974451212771188749869748393841e-44), SC_(0.4743587982081173781122087965978246042072e-44), SC_(1.0) }}, 
      {{ SC_(0.8407790785948902425542377499739496787682e-44), SC_(0.9487175964162347562244175931956492084145e-44), SC_(1.0) }}, 
      {{ SC_(0.1541428310757298778016102541618907744408e-43), SC_(0.1739315593429763719744765587525356882093e-43), SC_(1.0) }}, 
      {{ SC_(0.3222986467947079263124578041566807101945e-43), SC_(0.3636750786262233232193600773916655298922e-43), SC_(1.0) }}, 
      {{ SC_(0.7426881860921530475895766791436555495785e-43), SC_(0.8380338768343407013315688739894901340994e-43), SC_(1.0) }}, 
      {{ SC_(0.105097384824361280319279718746743709846e-42), SC_(0.1185896995520293445280521991494561510518e-42), SC_(1.0) }}, 
      {{ SC_(0.210194769648722560638559437493487419692e-42), SC_(0.2371793991040586890561043982989123021036e-42), SC_(1.0) }}, 
      {{ SC_(0.4666323886201640846176019512355420717163e-42), SC_(0.52653826601101028970455176422358531067e-42), SC_(1.0) }}, 
      {{ SC_(0.1223333559355565302916415926212096782608e-41), SC_(0.1380384102785621570306527598099669598243e-41), SC_(1.0) }}, 
      {{ SC_(0.2578389174357663410499662433253445681556e-41), SC_(0.2909400629009786585754880619133324239138e-41), SC_(1.0) }}, 
      {{ SC_(0.2960943655118338470861840609491592785395e-41), SC_(0.3341067135379173399836990624037344628966e-41), SC_(1.0) }}, 
      {{ SC_(0.7557202618103738463491673642682517695994e-41), SC_(0.8527389995787923400530473466840226968299e-41), SC_(1.0) }}, 
      {{ SC_(0.1465898323530191137893313517079581264932e-40), SC_(0.1654089129351705297477272073736614394871e-40), SC_(1.0) }}, 
      {{ SC_(0.4298903428855673810179817615616804707542e-40), SC_(0.4850793070476208308575447154009354402623e-40), SC_(1.0) }}, 
      {{ SC_(0.4803791265551905400833637384476161489642e-40), SC_(0.5420497987124157279688209918723341752276e-40), SC_(0.9999999999999999999999999999999999999999) }}, 
      {{ SC_(0.1055289847513733239771242274583970040145e-39), SC_(0.1190767079181896783695807335139632509788e-39), SC_(0.9999999999999999999999999999999999999999) }}, 
      {{ SC_(0.2015109230653016692500450852658398094265e-39), SC_(0.227380727529073011082233205257189905196e-39), SC_(0.9999999999999999999999999999999999999998) }}, 
      {{ SC_(0.7325049501519046019351739362618877290525e-39), SC_(0.8265433255457460713757641362399021627702e-39), SC_(0.9999999999999999999999999999999999999992) }}, 
      {{ SC_(0.1339665153968418641693291185028075750078e-38), SC_(0.1511650250621765838235665056990208282135e-38), SC_(0.9999999999999999999999999999999999999985) }}, 
      {{ SC_(0.2677046191439987831560976690835388936862e-38), SC_(0.3020723151773267572050253779518901717253e-38), SC_(0.999999999999999999999999999999999999997) }}, 
      {{ SC_(0.4980653348629733537806134066371931674319e-38), SC_(0.5620065477118294341833797281540012541512e-38), SC_(0.9999999999999999999999999999999999999944) }}, 
      {{ SC_(0.6613229117999040042200470598735932013487e-38), SC_(0.7462229963979548044442924939647721094874e-38), SC_(0.9999999999999999999999999999999999999925) }}, 
      {{ SC_(0.1548242965319156795913711730955404935546e-37), SC_(0.1747005107668316705149757196187806484869e-37), SC_(0.9999999999999999999999999999999999999825) }}, 
      {{ SC_(0.4146556501891822617936303213288858289615e-37), SC_(0.4678887971919177014040265951235884621123e-37), SC_(0.9999999999999999999999999999999999999532) }}, 
      {{ SC_(0.9169899847717825977881300331923883942907e-37), SC_(0.1034712395251710806479818721979201078743e-36), SC_(0.9999999999999999999999999999999999998965) }}, 
      {{ SC_(0.1401743180405455194869357938110469019064e-36), SC_(0.1581697802387722354144421623938376299412e-36), SC_(0.9999999999999999999999999999999999998418) }}, 
      {{ SC_(0.1945576912957096415426581064633919119024e-36), SC_(0.2195348456562787018647206880870297955178e-36), SC_(0.9999999999999999999999999999999999997805) }}, 
      {{ SC_(0.6257788193068770148365547155357311502081e-36), SC_(0.7061157829155071490944174116544753093472e-36), SC_(0.9999999999999999999999999999999999992939) }}, 
      {{ SC_(0.1082390914972224343528760935165450352846e-35), SC_(0.1221347359108108275138920730258033965505e-35), SC_(0.9999999999999999999999999999999999987787) }}, 
      {{ SC_(0.1694061057766321374547939115222498639949e-35), SC_(0.1911543205371304725231209426978241547223e-35), SC_(0.9999999999999999999999999999999999980885) }}, 
      {{ SC_(0.4157476136990655326859281227151399960547e-35), SC_(0.469120946067698479126142569921586497913e-35), SC_(0.9999999999999999999999999999999999953088) }}, 
      {{ SC_(0.7283681265086265937666854409047925692044e-35), SC_(0.8218754199287230086952619241467251109843e-35), SC_(0.9999999999999999999999999999999999917812) }}, 
      {{ SC_(0.2125163494676521664376074827660149555726e-34), SC_(0.2397990214064882285432839461962890817645e-34), SC_(0.9999999999999999999999999999999999760201) }}, 
      {{ SC_(0.2530711628583540298128114059620192234547e-34), SC_(0.2855602279620023372947687038386988804286e-34), SC_(0.999999999999999999999999999999999971444) }}, 
      {{ SC_(0.8643572969601960480494638860332170085101e-34), SC_(0.9753227668168746390533409248013332505622e-34), SC_(0.9999999999999999999999999999999999024677) }}, 
      {{ SC_(0.99805657801365854084424590887058919672e-34), SC_(0.1126186250213249491600342719979975982704e-33), SC_(0.9999999999999999999999999999999998873814) }}, 
      {{ SC_(0.2285833483419143806137872349711124495646e-33), SC_(0.2579286882139527639322447178720013355598e-33), SC_(0.9999999999999999999999999999999997420713) }}, 
      {{ SC_(0.5426235288674262982106993151912976763677e-33), SC_(0.6122850855498543097076270518307709592481e-33), SC_(0.9999999999999999999999999999999993877149) }}, 
      {{ SC_(0.1147672787261224070426617104882286355311e-32), SC_(0.1295010063788005409890233863705470341395e-32), SC_(0.9999999999999999999999999999999987049899) }}, 
      {{ SC_(0.22463880715206230259705675341401055879e-32), SC_(0.2534777501115735340046251758622995828684e-32), SC_(0.9999999999999999999999999999999974652225) }}, 
      {{ SC_(0.4454556413592197901478916560693101385393e-32), SC_(0.5026428655749137894397761320610666694693e-32), SC_(0.9999999999999999999999999999999949735713) }}, 
      {{ SC_(0.9167850888743889506336831720594191266931e-32), SC_(0.1034481194989668475298051221951978796736e-31), SC_(0.9999999999999999999999999999999896551881) }}, 
      {{ SC_(0.2029237383788489473978179376606301463249e-31), SC_(0.2289749188958332742407712486623796907403e-31), SC_(0.9999999999999999999999999999999771025081) }}, 
      {{ SC_(0.4422489809322529014977160404510081439987e-31), SC_(0.4990245367531747508971186530942781923233e-31), SC_(0.9999999999999999999999999999999500975463) }}, 
      {{ SC_(0.8427819595678069227982621602322463722706e-31), SC_(0.9509776055802459297555061290310693509558e-31), SC_(0.9999999999999999999999999999999049022394) }}, 
      {{ SC_(0.1894128825516700180187896525548839017318e-30), SC_(0.2137295506508135613325177084306249463745e-30), SC_(0.9999999999999999999999999999997862704493) }}, 
      {{ SC_(0.3460509137323572130893969054757060828136e-30), SC_(0.390476641809958306521950254784930239331e-30), SC_(0.9999999999999999999999999999996095233582) }}, 
      {{ SC_(0.7129452701155289322465925784842836259778e-30), SC_(0.8044725900776457681286359991257189545736e-30), SC_(0.9999999999999999999999999999991955274099) }}, 
      {{ SC_(0.1006606281422698106765835646474453774524e-29), SC_(0.1135833557424855221443633868642206855925e-29), SC_(0.9999999999999999999999999999988641664426) }}, 
      {{ SC_(0.2691237328241499384996035977623006944895e-29), SC_(0.3036736134897495655058606838487828118587e-29), SC_(0.9999999999999999999999999999969632638651) }}, 
      {{ SC_(0.53002073552022827485063776974422846038e-29), SC_(0.5980643560896661370936819930965482836573e-29), SC_(0.9999999999999999999999999999940193564391) }}, 
      {{ SC_(0.6328674258047448903166407618549998992304e-29), SC_(0.7141144188114391407566450273134713579864e-29), SC_(0.9999999999999999999999999999928588558119) }}, 
      {{ SC_(0.2089027321727668921272023434652731888509e-28), SC_(0.2357214909330836434674323280791160963504e-28), SC_(0.9999999999999999999999999999764278509067) }}, 
      {{ SC_(0.431842364003957104364921550167833797347e-28), SC_(0.4872819270113422778304421472654534392263e-28), SC_(0.9999999999999999999999999999512718072989) }}, 
      {{ SC_(0.5869689191576790243963724295243864109357e-28), SC_(0.6623235001100951114675477389355052037517e-28), SC_(0.999999999999999999999999999933767649989) }}, 
      {{ SC_(0.1659976352436858066871624892515432120194e-27), SC_(0.1873082733960948939621836113363260997334e-27), SC_(0.9999999999999999999999999998126917266039) }}, 
      {{ SC_(0.2259797844707783785531125574841037632032e-27), SC_(0.2549908809815603534966750948985043565705e-27), SC_(0.9999999999999999999999999997450091190184) }}, 
      {{ SC_(0.5880869455645201196495195879197812435557e-27), SC_(0.6635850578158372552104628507822996913944e-27), SC_(0.9999999999999999999999999993364149421842) }}, 
      {{ SC_(0.1210368873588132831231840717009055000898e-26), SC_(0.136575502145771107167093316323928936418e-26), SC_(0.9999999999999999999999999986342449785423) }}, 
      {{ SC_(0.2865917801972336300962667874631175760926e-26), SC_(0.3233841942353746978165316543252271930097e-26), SC_(0.9999999999999999999999999967661580576463) }}, 
      {{ SC_(0.6332274308614525819994844546119106938273e-26), SC_(0.7145206410174771386698068058159747695855e-26), SC_(0.9999999999999999999999999928547935898252) }}, 
      {{ SC_(0.1017015117562076843891927280903461796905e-25), SC_(0.1147578671278241071470420542046720634233e-25), SC_(0.9999999999999999999999999885242132872176) }}, 
      {{ SC_(0.1732407881343339865174865944566931617746e-25), SC_(0.1954812962219899413849001377507194449177e-25), SC_(0.999999999999999999999999980451870377801) }}, 
      {{ SC_(0.4851304131156321593400980501390172514877e-25), SC_(0.5474110514841189450665720204629142546924e-25), SC_(0.9999999999999999999999999452588948515881) }}, 
      {{ SC_(0.8195642344688286703600152101217105477795e-25), SC_(0.9247792082712082720339044529059539700692e-25), SC_(0.9999999999999999999999999075220791728792) }}, 
      {{ SC_(0.1869609713097047478340985963996916097412e-24), SC_(0.2109628650858126659649010477127478351642e-24), SC_(0.9999999999999999999999997890371349141873) }}, 
      {{ SC_(0.2530783866565756141965447805546793991855e-24), SC_(0.2855683791454228747266674274313813542172e-24), SC_(0.9999999999999999999999997144316208545771) }}, 
      {{ SC_(0.4209414052294289885709092151366397306124e-24), SC_(0.474981512228797723082223866616547403578e-24), SC_(0.9999999999999999999999995250184877712023) }}, 
      {{ SC_(0.1448614172287997697834930368987483835595e-23), SC_(0.1634586053169086194558576878083327447891e-23), SC_(0.9999999999999999999999983654139468309138) }}, 
      {{ SC_(0.3012998612797836509437815728233749567808e-23), SC_(0.3399804865168757552575507775525287643073e-23), SC_(0.9999999999999999999999966001951348312424) }}, 
      {{ SC_(0.415276141474016400714459480565419005095e-23), SC_(0.4685889466310888715323687240479993998499e-23), SC_(0.9999999999999999999999953141105336891113) }}, 
      {{ SC_(0.1204931390183540503963647385927016736362e-22), SC_(0.1359619478462541509417967524360939547446e-22), SC_(0.9999999999999999999999864038052153745849) }}, 
      {{ SC_(0.1993117661558407300079387840940773127252e-22), SC_(0.2248992446872631349043635494217604899453e-22), SC_(0.9999999999999999999999775100755312736865) }}, 
      {{ SC_(0.5135333031694984418963713908106404060216e-22), SC_(0.5794602809062059992419407432753169472345e-22), SC_(0.9999999999999999999999420539719093794001) }}, 
      {{ SC_(0.899483690375495720736892890190099236758e-22), SC_(0.1014958657361899781022539075381620547142e-21), SC_(0.9999999999999999999998985041342638100219) }}, 
      {{ SC_(0.1495718898928958003798630318006718936674e-21), SC_(0.1687738045382474786366114844967457859701e-21), SC_(0.9999999999999999999998312261954617525214) }}, 
      {{ SC_(0.4004143349189545415674843981449458618638e-21), SC_(0.4518191937289535418778128853745495698362e-21), SC_(0.9999999999999999999995481808062710464581) }}, 
      {{ SC_(0.6027338573124474618509081343250763374009e-21), SC_(0.6801123278944849878208640332552941589305e-21), SC_(0.9999999999999999999993198876721055150122) }}, 
      {{ SC_(0.1659584418309930229572620634728719046791e-20), SC_(0.1872640483657249799664013537449399617766e-20), SC_(0.9999999999999999999981273595163427502003) }}, 
      {{ SC_(0.2678244821868696143277384944057090132574e-20), SC_(0.3022075661378068793988187051769889525453e-20), SC_(0.999999999999999999996977924338621931206) }}, 
      {{ SC_(0.5242169890349582687359968492107897830579e-20), SC_(0.5915155294645836590589096407129433743023e-20), SC_(0.9999999999999999999940848447053541634094) }}, 
      {{ SC_(0.7847303335957885127235572164487720225878e-20), SC_(0.8854733602173995706713015709887803225844e-20), SC_(0.9999999999999999999911452663978260042933) }}, 
      {{ SC_(0.1543123850410999503479436223765675073594e-19), SC_(0.1741228805051983958166845695046398116561e-19), SC_(0.9999999999999999999825877119494801604183) }}, 
      {{ SC_(0.4775181844358503128246959748559596903306e-19), SC_(0.5388215712266861317995086503415856707862e-19), SC_(0.99999999999999999994611784287733138682) }}, 
      {{ SC_(0.6230335359741914917030257154567651767252e-19), SC_(0.7030180623951302655508677093605170542092e-19), SC_(0.9999999999999999999296981937604869734449) }}, 
      {{ SC_(0.1333737877121347004096484859664295541393e-18), SC_(0.1504962034909922627946995932175931040167e-18), SC_(0.9999999999999999998495037965090077372053) }}, 
      {{ SC_(0.272678641362033605222928850375652132243e-18), SC_(0.3076848982248274637704507517821273969355e-18), SC_(0.9999999999999999996923151017751725362295) }}, 
      {{ SC_(0.7848472665613653936552990969532928033914e-18), SC_(0.885605304939703219820034216816760452174e-18), SC_(0.99999999999999999911439469506029678018) }}, 
      {{ SC_(0.1596567770068200412154901801642381542479e-17), SC_(0.180153381060109581137526939833213468117e-17), SC_(0.9999999999999999981984661893989041886247) }}, 
      {{ SC_(0.3449535060248237706634344412748305330751e-17), SC_(0.3892383498149675248979402679995676281369e-17), SC_(0.9999999999999999961076165018503247510206) }}, 
      {{ SC_(0.4351665680924082666098176574998035448516e-17), SC_(0.4910328896519242978931639720387530850973e-17), SC_(0.9999999999999999950896711034807570210684) }}, 
      {{ SC_(0.9245716998221635790720235315021113819967e-17), SC_(0.1043267444565415210292590191714661224142e-16), SC_(0.9999999999999999895673255543458478970741) }}, 
      {{ SC_(0.2517825949792599072966925444205799067277e-16), SC_(0.2841062348118440801806623646517627970916e-16), SC_(0.9999999999999999715893765188155919819338) }}, 
      {{ SC_(0.3607757836945135819072677518803970997396e-16), SC_(0.4070918783134460417227759258926655100437e-16), SC_(0.9999999999999999592908121686553958277224) }}, 
      {{ SC_(0.6902950590186084176697045577952849271242e-16), SC_(0.7789145637455650616639975178325762794953e-16), SC_(0.9999999999999999221085436254434938336002) }}, 
      {{ SC_(0.1125254418367572150846966927417724946281e-15), SC_(0.1269713643368146509171410927223650268325e-15), SC_(0.9999999999999998730286356631853490828589) }}, 
      {{ SC_(0.4283825720300077181945663795659129391424e-15), SC_(0.4833779698254535301267982815421810779873e-15), SC_(0.9999999999999995166220301745464698732017) }}, 
      {{ SC_(0.5405621861962687634689528337617048237007e-15), SC_(0.6099591094234751315857573573713433261908e-15), SC_(0.9999999999999993900408905765248684142426) }}, 
      {{ SC_(0.1199026382331771015121724133223324315622e-14), SC_(0.1352956390621069391623702837955015493166e-14), SC_(0.9999999999999986470436093789306083762972) }}, 
      {{ SC_(0.3388160376379171188909733558602965786122e-14), SC_(0.3823129583484747580613317941389808261798e-14), SC_(0.9999999999999961768704165152524193866821) }}, 
      {{ SC_(0.4251160106447451902944578705501044169068e-14), SC_(0.4796920500102846351328633565382312006865e-14), SC_(0.9999999999999952030794998971536486713664) }}, 
      {{ SC_(0.1313415386649738336721782161475857719779e-13), SC_(0.1482030560038262349331825316596395555414e-13), SC_(0.9999999999999851796943996173765066817468) }}, 
      {{ SC_(0.1777897084111537684414372506580548360944e-13), SC_(0.2006142030951317354054567215576954023455e-13), SC_(0.9999999999999799385796904868264594543278) }}, 
      {{ SC_(0.5556494121154026410991377815662417560816e-13), SC_(0.6269832208398892455680747006005262348402e-13), SC_(0.9999999999999373016779160110754431925299) }}, 
      {{ SC_(0.9186150917630392376267423060198780149221e-13), SC_(0.1036546132124946068175722614185676168866e-12), SC_(0.9999999999998963453867875053931824277386) }}, 
      {{ SC_(0.2022372612257850033046224780264310538769e-12), SC_(0.228200312377628882307346737694658892409e-12), SC_(0.9999999999997717996876223711176926532623) }}, 
      {{ SC_(0.334987083645127414754938399710226804018e-12), SC_(0.3779924464312436744509548821977467036951e-12), SC_(0.9999999999996220075535687563255490451178) }}, 
      {{ SC_(0.9037920151860889816930466622579842805862e-12), SC_(0.1019820081323253936787897658201809797801e-11), SC_(0.9999999999989801799186767460632121023418) }}, 
      {{ SC_(0.1229327186921813641617973189568147063255e-11), SC_(0.1387147187266705574841551295246781201059e-11), SC_(0.9999999999986128528127332944251584487048) }}, 
      {{ SC_(0.1941944651959182088774014118826016783714e-11), SC_(0.2191249888923286935404641309633986461335e-11), SC_(0.9999999999978087501110767130645953586904) }}, 
      {{ SC_(0.6660515888823326235979038756340742111206e-11), SC_(0.7515587371056892484340940489030914565555e-11), SC_(0.999999999992484412628943107515659059511) }}, 
      {{ SC_(0.1305013996172332824130535300355404615402e-10), SC_(0.1472550606048923346284018897482637545021e-10), SC_(0.9999999999852744939395107665371598110252) }}, 
      {{ SC_(0.2306862860457226105381778324954211711884e-10), SC_(0.2603015993086296441348608813996585159423e-10), SC_(0.99999999997396984006913703558651391186) }}, 
      {{ SC_(0.464061636340495908825687365606427192688e-10), SC_(0.5236374826948694233006052031278254256924e-10), SC_(0.9999999999476362517305130576699394796872) }}, 
      {{ SC_(0.9020578728424766268290113657712936401367e-10), SC_(0.1017863311229943567634007843433802039614e-9), SC_(0.9999999998982136688770056432365992156566) }}, 
      {{ SC_(0.2017243178054073382554634008556604385376e-9), SC_(0.2276215177081760092443407256160138975684e-9), SC_(0.999999999772378482291823990755659274384) }}, 
      {{ SC_(0.4463814318178549456206383183598518371582e-9), SC_(0.5036875082415334987251679342248332272253e-9), SC_(0.9999999994963124917584665012748320657752) }}, 
      {{ SC_(0.7894043196898792302818037569522857666016e-9), SC_(0.8907473887532656624292837310188997818123e-9), SC_(0.9999999991092526112467343375707162689811) }}, 
      {{ SC_(0.1197530963281678850762546062469482421875e-8), SC_(0.1351268990918867631962395950793232393347e-8), SC_(0.9999999986487310090811323680376040492068) }}, 
      {{ SC_(0.3128908243610339923179708421230316162109e-8), SC_(0.3530594877843318503414910172348506997629e-8), SC_(0.9999999964694051221566814965850898276515) }}, 
      {{ SC_(0.654608101058329339139163494110107421875e-8), SC_(0.7386461438461727721842489523977686137653e-8), SC_(0.9999999926135385615382722781575104760223) }}, 
      {{ SC_(0.1037359531608217366738244891166687011719e-7), SC_(0.1170534884254671319566985248995045101925e-7), SC_(0.9999999882946511574532868043301475100495) }}, 
      {{ SC_(0.2613260008388351707253605127334594726563e-7), SC_(0.2948748151669259830348980474563029807727e-7), SC_(0.9999999705125184833074016965101952543697) }}, 
      {{ SC_(0.4653804097642932902090251445770263671875e-7), SC_(0.525125559152401230823420797240431154212e-7), SC_(0.9999999474874440847598769176579202759569) }}, 
      {{ SC_(0.8228098380413939594291150569915771484375e-7), SC_(0.9284414797271396176853241560056526014051e-7), SC_(0.9999999071558520272860382314675843994347) }}, 
      {{ SC_(0.1440129295815495424903929233551025390625e-6), SC_(0.1625011895322124534932667008476984221693e-6), SC_(0.9999998374988104677875465067332991523016) }}, 
      {{ SC_(0.373797803376874071545898914337158203125e-6), SC_(0.4217856540365096975937056642610100404098e-6), SC_(0.99999957821434596349030240629433573899) }}, 
      {{ SC_(0.72830744102247990667819976806640625e-6), SC_(0.8218069436902647194923144120911901417405e-6), SC_(0.9999991781930563097352805076855879088099) }}, 
      {{ SC_(0.10260146154905669391155242919921875e-5), SC_(0.1157733517254662264894221065154775581876e-5), SC_(0.9999988422664827453377351057789348452244) }}, 
      {{ SC_(0.2678315240700612775981426239013671875e-5), SC_(0.3022155120513748374723247514313931180799e-5), SC_(0.9999969778448794862516252767524856860688) }}, 
      {{ SC_(0.40205004552262835204601287841796875e-5), SC_(0.4536648954950918836538342339896039137139e-5), SC_(0.9999954633510450490811634616576601039609) }}, 
      {{ SC_(0.10320758519810624420642852783203125e-4), SC_(0.1164572890196433412287423508862147085112e-4), SC_(0.9999883542710980356658771257649113785291) }}, 
      {{ SC_(0.233581158681772649288177490234375e-4), SC_(0.2635681132346089850308780034445740445022e-4), SC_(0.9999736431886765391014969121996555425955) }}, 
      {{ SC_(0.4860912667936645448207855224609375e-4), SC_(0.5484952583250342934869652426491962534587e-4), SC_(0.9999451504741674965706513034757350803747) }}, 
      {{ SC_(0.0001085917465388774871826171875), SC_(0.0001225326640313436930517738593548252912385), SC_(0.9998774673359686563069482261406451747088) }}, 
      {{ SC_(0.000165569479577243328094482421875), SC_(0.0001868251497546456322442598271644064384812), SC_(0.9998131748502453543677557401728355935615) }}, 
      {{ SC_(0.0004721705918200314044952392578125), SC_(0.0005327874195307728646012144512357625925006), SC_(0.9994672125804692271353987855487642374075) }}, 
      {{ SC_(0.00095945619978010654449462890625), SC_(0.001082630055365222472802272152269070171599), SC_(0.9989173699446347775271977278477309298284) }}, 
      {{ SC_(0.0011034240014851093292236328125), SC_(0.001245080150435437151082626328085359462604), SC_(0.9987549198495645628489173736719146405374) }}, 
      {{ SC_(0.00225476245395839214324951171875), SC_(0.002544222668224971136268866790058243266433), SC_(0.9974557773317750288637311332099417567336) }}, 
      {{ SC_(0.006128217093646526336669921875), SC_(0.0069148659371010946376763193961158375309), SC_(0.9930851340628989053623236806038841624691) }}, 
      {{ SC_(0.01089772023260593414306640625), SC_(0.01229627370763712993609092392080824128196), SC_(0.987703726292362870063909076079191758718) }}, 
      {{ SC_(0.0229592286050319671630859375), SC_(0.02590216393432758991206927422057375200344), SC_(0.9740978360656724100879307257794262479966) }}, 
      {{ SC_(0.043352998793125152587890625), SC_(0.04888799071126766325637634356499925915047), SC_(0.9511120092887323367436236564350007408495) }}, 
      {{ SC_(0.06324388086795806884765625), SC_(0.07126804593959971882312270799434219648871), SC_(0.9287319540604002811768772920056578035113) }}, 
      {{ SC_(0.2158693373203277587890625), SC_(0.2398511631288111077158786048968679107576), SC_(0.7601488368711888922841213951031320892424) }}, 
      {{ SC_(0.334280669689178466796875), SC_(0.3636043520990431448970776140491250415292), SC_(0.6363956479009568551029223859508749584708) }}
   } };


