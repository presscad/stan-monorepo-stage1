//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

   static const boost::array<boost::array<typename table_type<T>::type, 3>, 224> bessel_j_int_data = {{
      {{ SC_(0.0), SC_(0.1730655412757187150418758392333984375e-5), SC_(0.999999999999251207960573702716351702855e0) }}, 
      {{ SC_(0.0), SC_(0.216575062950141727924346923828125e-5), SC_(0.9999999999988273810527038974545295287162e0) }}, 
      {{ SC_(0.0), SC_(0.72700195232755504548549652099609375e-5), SC_(0.9999999999867867040328417323221266089012e0) }}, 
      {{ SC_(0.0), SC_(0.14000004739500582218170166015625e-4), SC_(0.9999999999509999668240905595691881208684e0) }}, 
      {{ SC_(0.0), SC_(0.17196454791701398789882659912109375e-4), SC_(0.9999999999260704856506088935623108659333e0) }}, 
      {{ SC_(0.0), SC_(0.60085076256655156612396240234375e-4), SC_(0.9999999990974459030116346626772683432438e0) }}, 
      {{ SC_(0.0), SC_(0.116783194243907928466796875e-3), SC_(0.9999999965904213884537241019212664253672e0) }}, 
      {{ SC_(0.0), SC_(0.149052008055150508880615234375e-3), SC_(0.9999999944458747313939138453006009257493e0) }}, 
      {{ SC_(0.0), SC_(0.3985252114944159984588623046875e-3), SC_(0.9999999602944143449661387732367591439684e0) }}, 
      {{ SC_(0.0), SC_(0.63875340856611728668212890625e-3), SC_(0.999999897998523362367123063793585129913e0) }}, 
      {{ SC_(0.0), SC_(0.10718167759478092193603515625e-2), SC_(0.999999712802220319854399500739679836503e0) }}, 
      {{ SC_(0.0), SC_(0.302191521041095256805419921875e-2), SC_(0.9999977170084182855294667634808613841995e0) }}, 
      {{ SC_(0.0), SC_(0.499413348734378814697265625e-2), SC_(0.9999937646673975145784086810883184951737e0) }}, 
      {{ SC_(0.0), SC_(0.928423367440700531005859375e-2), SC_(0.9999784508673620039917059777810212577274e0) }}, 
      {{ SC_(0.0), SC_(0.241700224578380584716796875e-1), SC_(0.9998539578359781705487991537766139314417e0) }}, 
      {{ SC_(0.0), SC_(0.6227754056453704833984375e-1), SC_(0.9990306120021848197073447709696842002313e0) }}, 
      {{ SC_(0.0), SC_(0.12234418094158172607421875e0), SC_(0.9962614745793813396644750956695984663693e0) }}, 
      {{ SC_(0.0), SC_(0.249557673931121826171875e0), SC_(0.9844907414458467656383892255940207494775e0) }}, 
      {{ SC_(0.0), SC_(0.4912221431732177734375e0), SC_(0.9405788968099850208754506401326367253837e0) }}, 
      {{ SC_(0.0), SC_(0.98384749889373779296875e0), SC_(0.7722629604360946893704391598535972411534e0) }}, 
      {{ SC_(0.0), SC_(0.11576130390167236328125e1), SC_(0.69201921296869073470763460902488953195e0) }}, 
      {{ SC_(0.0), SC_(0.3451677799224853515625e1), SC_(-0.3729999217923199419780408144861949608561e0) }}, 
      {{ SC_(0.0), SC_(0.788237094879150390625e1), SC_(0.1981996630505566917360863478152806154613e0) }}, 
      {{ SC_(0.0), SC_(0.15848876953125e2), SC_(-0.1592255309532503835966920565319209366427e0) }}, 
      {{ SC_(0.1e1), SC_(0.553809732082299888134002685546875e-4), SC_(0.276904865934989734483098712606972348472e-4) }}, 
      {{ SC_(0.1e1), SC_(0.69304020144045352935791015625e-4), SC_(0.3465201005121827144301015458593023209872e-4) }}, 
      {{ SC_(0.1e1), SC_(0.23264062474481761455535888671875e-3), SC_(0.1163203115854777552927670265943683111663e-3) }}, 
      {{ SC_(0.1e1), SC_(0.4480001516640186309814453125e-3), SC_(0.224000070212291655064298940047799298227e-3) }}, 
      {{ SC_(0.1e1), SC_(0.5502865533344447612762451171875e-3), SC_(0.2751432662525235957510064043924201271744e-3) }}, 
      {{ SC_(0.1e1), SC_(0.19227224402129650115966796875e-2), SC_(0.9613607758541307952398436842542503763082e-3) }}, 
      {{ SC_(0.1e1), SC_(0.37370622158050537109375e-2), SC_(0.1868527846001727517468459203726183793639e-2) }}, 
      {{ SC_(0.1e1), SC_(0.47696642577648162841796875e-2), SC_(0.2384825347112756329700145763683641710414e-2) }}, 
      {{ SC_(0.1e1), SC_(0.1275280676782131195068359375e-1), SC_(0.6376273757226442847790070686813990559145e-2) }}, 
      {{ SC_(0.1e1), SC_(0.20440109074115753173828125e-1), SC_(0.102195208064807658405217565669384689625e-1) }}, 
      {{ SC_(0.1e1), SC_(0.3429813683032989501953125e-1), SC_(0.1714654684930302330423492169172745899688e-1) }}, 
      {{ SC_(0.1e1), SC_(0.96701286733150482177734375e-1), SC_(0.4829414868544472860291893155827576361067e-1) }}, 
      {{ SC_(0.1e1), SC_(0.159812271595001220703125e0), SC_(0.7965130716107429048780909632824084802407e-1) }}, 
      {{ SC_(0.1e1), SC_(0.297095477581024169921875e0), SC_(0.1469147961900711346572957228234698754028e0) }}, 
      {{ SC_(0.1e1), SC_(0.77344071865081787109375e0), SC_(0.3585147006385292414727602076757818503575e0) }}, 
      {{ SC_(0.1e1), SC_(0.1992881298065185546875e1), SC_(0.5771736137851551766101983376499833110574e0) }}, 
      {{ SC_(0.1e1), SC_(0.3915013790130615234375e1), SC_(-0.3315763536880066424018546732060494035118e-1) }}, 
      {{ SC_(0.1e1), SC_(0.79858455657958984375e1), SC_(0.2325970018905132078980792992006627584192e0) }}, 
      {{ SC_(0.1e1), SC_(0.1571910858154296875e2), SC_(0.1373449658609949106151643744232618350175e0) }}, 
      {{ SC_(0.1e1), SC_(0.31483119964599609375e2), SC_(-0.9230877498012981860222086238303332873573e-1) }}, 
      {{ SC_(0.4e1), SC_(0.553809732082299888134002685546875e-4), SC_(0.2449689884414968964700618717685524683171e-19) }}, 
      {{ SC_(0.4e1), SC_(0.69304020144045352935791015625e-4), SC_(0.6007620436965929637530930219443973179641e-19) }}, 
      {{ SC_(0.4e1), SC_(0.23264062474481761455535888671875e-3), SC_(0.7628005478429104492672012434718507350272e-17) }}, 
      {{ SC_(0.4e1), SC_(0.4480001516640186309814453125e-3), SC_(0.1049014316653821463646665194851778246401e-15) }}, 
      {{ SC_(0.4e1), SC_(0.5502865533344447612762451171875e-3), SC_(0.2387945284954097519631184175866877863264e-15) }}, 
      {{ SC_(0.4e1), SC_(0.19227224402129650115966796875e-2), SC_(0.3559058080985751663501872629042355217152e-13) }}, 
      {{ SC_(0.4e1), SC_(0.37370622158050537109375e-2), SC_(0.5079135337601192358742525894357081341335e-12) }}, 
      {{ SC_(0.4e1), SC_(0.47696642577648162841796875e-2), SC_(0.1347781590846459623440987284254345472313e-11) }}, 
      {{ SC_(0.4e1), SC_(0.1275280676782131195068359375e-1), SC_(0.6887924230376394398803439333202892325557e-10) }}, 
      {{ SC_(0.4e1), SC_(0.20440109074115753173828125e-1), SC_(0.4545613845374467200233204286239376175147e-9) }}, 
      {{ SC_(0.4e1), SC_(0.3429813683032989501953125e-1), SC_(0.3603506796835261381553751482886494436605e-8) }}, 
      {{ SC_(0.4e1), SC_(0.96701286733150482177734375e-1), SC_(0.2276117732048184291309579825404846223101e-6) }}, 
      {{ SC_(0.4e1), SC_(0.159812271595001220703125e0), SC_(0.1696502961325871806891524286212542749233e-5) }}, 
      {{ SC_(0.4e1), SC_(0.297095477581024169921875e0), SC_(0.2019926506375704595965844529208340579256e-4) }}, 
      {{ SC_(0.4e1), SC_(0.77344071865081787109375e0), SC_(0.9043871099795724296870802463629379435165e-3) }}, 
      {{ SC_(0.4e1), SC_(0.1992881298065185546875e1), SC_(0.3356363239882888737614531598548044804195e-1) }}, 
      {{ SC_(0.4e1), SC_(0.3915013790130615234375e1), SC_(0.2683403769106168710689421055914199402732e0) }}, 
      {{ SC_(0.4e1), SC_(0.79858455657958984375e1), SC_(-0.1019714387996719292888771314960256244029e0) }}, 
      {{ SC_(0.4e1), SC_(0.1571910858154296875e2), SC_(-0.1970617873757679766451608652880933303855e0) }}, 
      {{ SC_(0.4e1), SC_(0.31483119964599609375e2), SC_(0.1274270375173584709656744808050405443416e0) }}, 
      {{ SC_(0.7e1), SC_(0.553809732082299888134002685546875e-4), SC_(0.2476758015173796525820991581584477984471e-35) }}, 
      {{ SC_(0.7e1), SC_(0.69304020144045352935791015625e-4), SC_(0.1190333036597015037788087962950721904204e-34) }}, 
      {{ SC_(0.7e1), SC_(0.23264062474481761455535888671875e-3), SC_(0.5716870852680826502230510205353692076762e-31) }}, 
      {{ SC_(0.7e1), SC_(0.4480001516640186309814453125e-3), SC_(0.561444224078444008798450658023844580616e-29) }}, 
      {{ SC_(0.7e1), SC_(0.5502865533344447612762451171875e-3), SC_(0.2368545839293556062239215049355950751334e-28) }}, 
      {{ SC_(0.7e1), SC_(0.19227224402129650115966796875e-2), SC_(0.1505828833808392807660517316033033280684e-24) }}, 
      {{ SC_(0.7e1), SC_(0.37370622158050537109375e-2), SC_(0.1577871390165051118291058054008029867733e-22) }}, 
      {{ SC_(0.7e1), SC_(0.47696642577648162841796875e-2), SC_(0.8705101764884624738964439520067718158933e-22) }}, 
      {{ SC_(0.7e1), SC_(0.1275280676782131195068359375e-1), SC_(0.8503500497157549233110373576875716028951e-19) }}, 
      {{ SC_(0.7e1), SC_(0.20440109074115753173828125e-1), SC_(0.2310661278306557800428208671429361931635e-17) }}, 
      {{ SC_(0.7e1), SC_(0.3429813683032989501953125e-1), SC_(0.8654405276396266715021848331684138021568e-16) }}, 
      {{ SC_(0.7e1), SC_(0.96701286733150482177734375e-1), SC_(0.1225344911694889641798963820236998213373e-12) }}, 
      {{ SC_(0.7e1), SC_(0.159812271595001220703125e0), SC_(0.4123668359663111441088023707096475138751e-11) }}, 
      {{ SC_(0.7e1), SC_(0.297095477581024169921875e0), SC_(0.3158156744651217917953769670307028606449e-9) }}, 
      {{ SC_(0.7e1), SC_(0.77344071865081787109375e0), SC_(0.251896150858704683595843840399835306166e-6) }}, 
      {{ SC_(0.7e1), SC_(0.1992881298065185546875e1), SC_(0.1707853166377511336641576065559156632457e-3) }}, 
      {{ SC_(0.7e1), SC_(0.3915013790130615234375e1), SC_(0.1335220837033977061080155342538527713965e-1) }}, 
      {{ SC_(0.7e1), SC_(0.79858455657958984375e1), SC_(0.3197732082032941630469007231253521918143e0) }}, 
      {{ SC_(0.7e1), SC_(0.1571910858154296875e2), SC_(0.1523464020656448663148336960516768275145e0) }}, 
      {{ SC_(0.7e1), SC_(0.31483119964599609375e2), SC_(-0.8465752063992111585817831175823765390968e-2) }}, 
      {{ SC_(0.1e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.7303698611664865207490004658067936181905e-52) }}, 
      {{ SC_(0.1e2), SC_(0.69304020144045352935791015625e-4), SC_(0.6878936281621022752851314176441951633029e-51) }}, 
      {{ SC_(0.1e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.1249662001772833555544044498679159797243e-45) }}, 
      {{ SC_(0.1e2), SC_(0.4480001516640186309814453125e-3), SC_(0.87643279255017773967807642045361302034e-43) }}, 
      {{ SC_(0.1e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.6852136624817352900940351580328586337538e-42) }}, 
      {{ SC_(0.1e2), SC_(0.19227224402129650115966796875e-2), SC_(0.185824479115402751843849340758426235854e-36) }}, 
      {{ SC_(0.1e2), SC_(0.37370622158050537109375e-2), SC_(0.1429684321223564675360504319868530544464e-33) }}, 
      {{ SC_(0.1e2), SC_(0.47696642577648162841796875e-2), SC_(0.1639890621444124727733839773586431172039e-32) }}, 
      {{ SC_(0.1e2), SC_(0.1275280676782131195068359375e-1), SC_(0.306191547516836368220168038780704053939e-28) }}, 
      {{ SC_(0.1e2), SC_(0.20440109074115753173828125e-1), SC_(0.3425823439848955129914050150766420797628e-26) }}, 
      {{ SC_(0.1e2), SC_(0.3429813683032989501953125e-1), SC_(0.6062205935674056071761047413439550035471e-24) }}, 
      {{ SC_(0.1e2), SC_(0.96701286733150482177734375e-1), SC_(0.1923832425983654541213096146081906580397e-19) }}, 
      {{ SC_(0.1e2), SC_(0.159812271595001220703125e0), SC_(0.2922712946223807891584380230043171121063e-17) }}, 
      {{ SC_(0.1e2), SC_(0.297095477581024169921875e0), SC_(0.143888516723819817784418267406968074987e-14) }}, 
      {{ SC_(0.1e2), SC_(0.77344071865081787109375e0), SC_(0.2033758816108020473655970022244540004408e-10) }}, 
      {{ SC_(0.1e2), SC_(0.1992881298065185546875e1), SC_(0.242885590788180736747780657352089100395e-6) }}, 
      {{ SC_(0.1e2), SC_(0.3915013790130615234375e1), SC_(0.1598475267744058553357687546625030272909e-3) }}, 
      {{ SC_(0.1e2), SC_(0.79858455657958984375e1), SC_(0.60056972136838046146179075502942356573e-1) }}, 
      {{ SC_(0.1e2), SC_(0.1571910858154296875e2), SC_(-0.1842232590397531945311647766302288337231e0) }}, 
      {{ SC_(0.1e2), SC_(0.31483119964599609375e2), SC_(-0.9317261959891319658027121347121001915601e-1) }}, 
      {{ SC_(0.13e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.90368551918725968389007265700993262299e-69) }}, 
      {{ SC_(0.13e2), SC_(0.69304020144045352935791015625e-4), SC_(0.1667974085958167624378345556115399941477e-67) }}, 
      {{ SC_(0.13e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.1146151324192891686284768890985563371943e-60) }}, 
      {{ SC_(0.13e2), SC_(0.4480001516640186309814453125e-3), SC_(0.5740448587965102107018898696167719687858e-57) }}, 
      {{ SC_(0.13e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.8317358972729155842535186608238358987262e-56) }}, 
      {{ SC_(0.13e2), SC_(0.19227224402129650115966796875e-2), SC_(0.9621558980749171469364024498494388216795e-49) }}, 
      {{ SC_(0.13e2), SC_(0.37370622158050537109375e-2), SC_(0.5435304733189136019244042387714022185558e-45) }}, 
      {{ SC_(0.13e2), SC_(0.47696642577648162841796875e-2), SC_(0.1296197228784403471129989731886036646855e-43) }}, 
      {{ SC_(0.13e2), SC_(0.1275280676782131195068359375e-1), SC_(0.4625978489147388510480567448018715189249e-38) }}, 
      {{ SC_(0.13e2), SC_(0.20440109074115753173828125e-1), SC_(0.2131121530101465666113363379817102327031e-35) }}, 
      {{ SC_(0.13e2), SC_(0.3429813683032989501953125e-1), SC_(0.1781711933682478816925141204995206372152e-32) }}, 
      {{ SC_(0.13e2), SC_(0.96701286733150482177734375e-1), SC_(0.1267291457925455878167599468504869327715e-26) }}, 
      {{ SC_(0.13e2), SC_(0.159812271595001220703125e0), SC_(0.8690870700737698910678361841372229152816e-24) }}, 
      {{ SC_(0.13e2), SC_(0.297095477581024169921875e0), SC_(0.2749753181518427631420704990495067851464e-20) }}, 
      {{ SC_(0.13e2), SC_(0.77344071865081787109375e0), SC_(0.6874485945761929731188960123719668004339e-15) }}, 
      {{ SC_(0.13e2), SC_(0.1992881298065185546875e1), SC_(0.1427954947280088715244535777966915467592e-9) }}, 
      {{ SC_(0.13e2), SC_(0.3915013790130615234375e1), SC_(0.7548925903672885635112989058254310604162e-6) }}, 
      {{ SC_(0.13e2), SC_(0.79858455657958984375e1), SC_(0.3214379121675310487741347594390187230881e-2) }}, 
      {{ SC_(0.13e2), SC_(0.1571910858154296875e2), SC_(0.2562871752817527993867029711304921017067e0) }}, 
      {{ SC_(0.13e2), SC_(0.31483119964599609375e2), SC_(0.135452434319841135048770973964056570279e0) }}, 
      {{ SC_(0.16e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.5710443102859793594686693457798971291695e-86) }}, 
      {{ SC_(0.16e2), SC_(0.69304020144045352935791015625e-4), SC_(0.2065548122783126765855808525012370612477e-84) }}, 
      {{ SC_(0.16e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.5368702794457035352466622003877382747158e-76) }}, 
      {{ SC_(0.16e2), SC_(0.4480001516640186309814453125e-3), SC_(0.1920220273734407205690092457873836811378e-71) }}, 
      {{ SC_(0.16e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.5156118426330840464377189920132922032504e-70) }}, 
      {{ SC_(0.16e2), SC_(0.19227224402129650115966796875e-2), SC_(0.2544286257456308178600141145465753228241e-61) }}, 
      {{ SC_(0.16e2), SC_(0.37370622158050537109375e-2), SC_(0.1055323568504563665150514946643052879562e-56) }}, 
      {{ SC_(0.16e2), SC_(0.47696642577648162841796875e-2), SC_(0.5232452376007528048513570920264122109991e-55) }}, 
      {{ SC_(0.16e2), SC_(0.1275280676782131195068359375e-1), SC_(0.3569372759580808303489639154371020886878e-48) }}, 
      {{ SC_(0.16e2), SC_(0.20440109074115753173828125e-1), SC_(0.6770631088264124985080490485409279874034e-45) }}, 
      {{ SC_(0.16e2), SC_(0.3429813683032989501953125e-1), SC_(0.2674369558860517619389933396711866115561e-41) }}, 
      {{ SC_(0.16e2), SC_(0.96701286733150482177734375e-1), SC_(0.4263407059281994448315250268426546365419e-34) }}, 
      {{ SC_(0.16e2), SC_(0.159812271595001220703125e0), SC_(0.1319773345595717550011326018119444329018e-30) }}, 
      {{ SC_(0.16e2), SC_(0.297095477581024169921875e0), SC_(0.2683325671969811781305622600203263139886e-26) }}, 
      {{ SC_(0.16e2), SC_(0.77344071865081787109375e0), SC_(0.1185527072917230718908112159994283095826e-19) }}, 
      {{ SC_(0.16e2), SC_(0.1992881298065185546875e1), SC_(0.4257913764415272936226850400127709560274e-13) }}, 
      {{ SC_(0.16e2), SC_(0.3915013790130615234375e1), SC_(0.1770596374018406424364588196143722326332e-8) }}, 
      {{ SC_(0.16e2), SC_(0.79858455657958984375e1), SC_(0.7609462131466514170142031981046135155552e-4) }}, 
      {{ SC_(0.16e2), SC_(0.1571910858154296875e2), SC_(0.1598242323049512757290685523586043599273e0) }}, 
      {{ SC_(0.16e2), SC_(0.31483119964599609375e2), SC_(-0.146616929844240669724265072627562678578e0) }}, 
      {{ SC_(0.19e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.2085386435150050836259354457009000018077e-103) }}, 
      {{ SC_(0.19e2), SC_(0.69304020144045352935791015625e-4), SC_(0.1478242165594325382694493377958682108845e-101) }}, 
      {{ SC_(0.19e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.1453319211512903213205953436626128066329e-91) }}, 
      {{ SC_(0.19e2), SC_(0.4480001516640186309814453125e-3), SC_(0.3712107285598227397108662690263089748287e-86) }}, 
      {{ SC_(0.19e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.1847245305223723518947855245367191928343e-84) }}, 
      {{ SC_(0.19e2), SC_(0.19227224402129650115966796875e-2), SC_(0.3888219252235519964245528947552171853277e-74) }}, 
      {{ SC_(0.19e2), SC_(0.37370622158050537109375e-2), SC_(0.1184163364577840228862020640686836979404e-68) }}, 
      {{ SC_(0.19e2), SC_(0.47696642577648162841796875e-2), SC_(0.1220685316325757321764623390231984663671e-66) }}, 
      {{ SC_(0.19e2), SC_(0.1275280676782131195068359375e-1), SC_(0.1591638310631743076506768378115511870553e-58) }}, 
      {{ SC_(0.19e2), SC_(0.20440109074115753173828125e-1), SC_(0.1243123177590827411934225161624922624915e-54) }}, 
      {{ SC_(0.19e2), SC_(0.3429813683032989501953125e-1), SC_(0.2319899218435133188992825576466373416419e-50) }}, 
      {{ SC_(0.19e2), SC_(0.96701286733150482177734375e-1), SC_(0.8288911503438383816925041924523248045712e-42) }}, 
      {{ SC_(0.19e2), SC_(0.159812271595001220703125e0), SC_(0.115821498784548972023307498969902449394e-37) }}, 
      {{ SC_(0.19e2), SC_(0.297095477581024169921875e0), SC_(0.1513146789392266259407994247748973151373e-32) }}, 
      {{ SC_(0.19e2), SC_(0.77344071865081787109375e0), SC_(0.1180867041363348335303085045154147913528e-24) }}, 
      {{ SC_(0.19e2), SC_(0.1992881298065185546875e1), SC_(0.7309651660473666120687072805302589654808e-17) }}, 
      {{ SC_(0.19e2), SC_(0.3915013790130615234375e1), SC_(0.2364159870071755910484486348587559990813e-11) }}, 
      {{ SC_(0.19e2), SC_(0.79858455657958984375e1), SC_(0.9689789089192189055495551850283928885267e-6) }}, 
      {{ SC_(0.19e2), SC_(0.1571910858154296875e2), SC_(0.28988183636629975718412063879767316272e-1) }}, 
      {{ SC_(0.19e2), SC_(0.31483119964599609375e2), SC_(0.1404351655526923900119491455044344208598e0) }}, 
      {{ SC_(0.22e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.4791884438276096956171867526066745487233e-121) }}, 
      {{ SC_(0.22e2), SC_(0.69304020144045352935791015625e-4), SC_(0.6656698862399030252104289006319409158079e-119) }}, 
      {{ SC_(0.22e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.2475458914860796896424360165211198402136e-107) }}, 
      {{ SC_(0.22e2), SC_(0.4480001516640186309814453125e-3), SC_(0.4515366894275771826117281426200239790956e-101) }}, 
      {{ SC_(0.22e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.4164178287432561100733955741346219769583e-99) }}, 
      {{ SC_(0.22e2), SC_(0.19227224402129650115966796875e-2), SC_(0.3738854595795469765521076338466195179729e-87) }}, 
      {{ SC_(0.22e2), SC_(0.37370622158050537109375e-2), SC_(0.8360661820524098792008512761880716972576e-81) }}, 
      {{ SC_(0.22e2), SC_(0.47696642577648162841796875e-2), SC_(0.1791864672483119204014438872980421431477e-78) }}, 
      {{ SC_(0.22e2), SC_(0.1275280676782131195068359375e-1), SC_(0.4465806266019354303051149660509529893234e-69) }}, 
      {{ SC_(0.22e2), SC_(0.20440109074115753173828125e-1), SC_(0.1436157691171859834871864549854120137171e-64) }}, 
      {{ SC_(0.22e2), SC_(0.3429813683032989501953125e-1), SC_(0.1266250352189026976463935184908537726894e-59) }}, 
      {{ SC_(0.22e2), SC_(0.96701286733150482177734375e-1), SC_(0.1014002264944669915985752126502534659735e-49) }}, 
      {{ SC_(0.22e2), SC_(0.159812271595001220703125e0), SC_(0.6395517348407679453466968468982951315152e-45) }}, 
      {{ SC_(0.22e2), SC_(0.297095477581024169921875e0), SC_(0.5368707332343228506070497601994580522396e-39) }}, 
      {{ SC_(0.22e2), SC_(0.77344071865081787109375e0), SC_(0.7398504152815100288293238816236231544857e-30) }}, 
      {{ SC_(0.22e2), SC_(0.1992881298065185546875e1), SC_(0.7877708523407809449378036883914301743673e-21) }}, 
      {{ SC_(0.22e2), SC_(0.3915013790130615234375e1), SC_(0.1968332845994952491334209201789498977283e-14) }}, 
      {{ SC_(0.22e2), SC_(0.79858455657958984375e1), SC_(0.7448464245775065475039475038584227288619e-8) }}, 
      {{ SC_(0.22e2), SC_(0.1571910858154296875e2), SC_(0.253851170309502550500960913045849958251e-2) }}, 
      {{ SC_(0.22e2), SC_(0.31483119964599609375e2), SC_(-0.8447893849187497539115391467530479019211e-1) }}, 
      {{ SC_(0.25e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.7372571830959398154087818458405571713543e-139) }}, 
      {{ SC_(0.25e2), SC_(0.69304020144045352935791015625e-4), SC_(0.2007082018704239928877827931765826257223e-136) }}, 
      {{ SC_(0.25e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.282321085875648461583736420544653624557e-123) }}, 
      {{ SC_(0.25e2), SC_(0.4480001516640186309814453125e-3), SC_(0.3677548883718449906250285120192357358526e-116) }}, 
      {{ SC_(0.25e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.6285313494759937735919237336354498066612e-114) }}, 
      {{ SC_(0.25e2), SC_(0.19227224402129650115966796875e-2), SC_(0.240723943542042702532722602099509196343e-100) }}, 
      {{ SC_(0.25e2), SC_(0.37370622158050537109375e-2), SC_(0.3952415336587423864493642493686435620558e-93) }}, 
      {{ SC_(0.25e2), SC_(0.47696642577648162841796875e-2), SC_(0.1761163090097583722535523692248334183587e-90) }}, 
      {{ SC_(0.25e2), SC_(0.1275280676782131195068359375e-1), SC_(0.838973477506519849649546640592049467827e-80) }}, 
      {{ SC_(0.25e2), SC_(0.20440109074115753173828125e-1), SC_(0.1110920317250862811627432685131862921107e-74) }}, 
      {{ SC_(0.25e2), SC_(0.3429813683032989501953125e-1), SC_(0.4627673735504195531564801614260252853823e-69) }}, 
      {{ SC_(0.25e2), SC_(0.96701286733150482177734375e-1), SC_(0.830561324288197807079744142399604541678e-58) }}, 
      {{ SC_(0.25e2), SC_(0.159812271595001220703125e0), SC_(0.236456302063194497551168460901108346276e-52) }}, 
      {{ SC_(0.25e2), SC_(0.297095477581024169921875e0), SC_(0.1275371942824651350612111302983155850293e-45) }}, 
      {{ SC_(0.25e2), SC_(0.77344071865081787109375e0), SC_(0.3103000869941400473392593242837244578633e-35) }}, 
      {{ SC_(0.25e2), SC_(0.1992881298065185546875e1), SC_(0.5676014969386446596753686198525691279888e-25) }}, 
      {{ SC_(0.25e2), SC_(0.3915013790130615234375e1), SC_(0.1090825721430814617531511126945649824391e-17) }}, 
      {{ SC_(0.25e2), SC_(0.79858455657958984375e1), SC_(0.3734200809691738263209576777640843925841e-10) }}, 
      {{ SC_(0.25e2), SC_(0.1571910858154296875e2), SC_(0.1291120784936711314245621877597952164143e-3) }}, 
      {{ SC_(0.25e2), SC_(0.31483119964599609375e2), SC_(-0.7461962297933840624621930608252220218503e-1) }}, 
      {{ SC_(0.28e2), SC_(0.553809732082299888134002685546875e-4), SC_(0.7963713582106584412097140308116466491608e-157) }}, 
      {{ SC_(0.28e2), SC_(0.69304020144045352935791015625e-4), SC_(0.4248692230753312125913578638497606609336e-154) }}, 
      {{ SC_(0.28e2), SC_(0.23264062474481761455535888671875e-3), SC_(0.2260553821923174448109780057299133388939e-139) }}, 
      {{ SC_(0.28e2), SC_(0.4480001516640186309814453125e-3), SC_(0.2102847637959861796417097898716140319015e-131) }}, 
      {{ SC_(0.28e2), SC_(0.5502865533344447612762451171875e-3), SC_(0.6660525810149796134788024971104638208402e-129) }}, 
      {{ SC_(0.28e2), SC_(0.19227224402129650115966796875e-2), SC_(0.108813792122284445419802118573486294617e-113) }}, 
      {{ SC_(0.28e2), SC_(0.37370622158050537109375e-2), SC_(0.1311802444742152354234077144037248874522e-105) }}, 
      {{ SC_(0.28e2), SC_(0.47696642577648162841796875e-2), SC_(0.1215284288581256977996490020569407519253e-102) }}, 
      {{ SC_(0.28e2), SC_(0.1275280676782131195068359375e-1), SC_(0.1106574120737639697400622354620027455407e-90) }}, 
      {{ SC_(0.28e2), SC_(0.20440109074115753173828125e-1), SC_(0.6033198112217245150379653252026122716124e-85) }}, 
      {{ SC_(0.28e2), SC_(0.3429813683032989501953125e-1), SC_(0.1187379908091547229246861752037218903857e-78) }}, 
      {{ SC_(0.28e2), SC_(0.96701286733150482177734375e-1), SC_(0.4776253533970672888906190995310047058597e-66) }}, 
      {{ SC_(0.28e2), SC_(0.159812271595001220703125e0), SC_(0.6137721383009946630525985606230109474371e-60) }}, 
      {{ SC_(0.28e2), SC_(0.297095477581024169921875e0), SC_(0.2127051389870186274825552068510907743209e-52) }}, 
      {{ SC_(0.28e2), SC_(0.77344071865081787109375e0), SC_(0.9135584911756594671676404048881870523782e-41) }}, 
      {{ SC_(0.28e2), SC_(0.1992881298065185546875e1), SC_(0.2868280579406050057547310818758384973257e-29) }}, 
      {{ SC_(0.28e2), SC_(0.3915013790130615234375e1), SC_(0.4227077578718476642466348871890940509389e-21) }}, 
      {{ SC_(0.28e2), SC_(0.79858455657958984375e1), SC_(0.1291218836633488658985438527652338235293e-12) }}, 
      {{ SC_(0.28e2), SC_(0.1571910858154296875e2), SC_(0.4222984862431763788622725393431592171924e-5) }}, 
      {{ SC_(0.28e2), SC_(0.31483119964599609375e2), SC_(0.1996895117755311022877682593279374977116e0) }}
   }};


