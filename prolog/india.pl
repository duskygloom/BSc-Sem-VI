/* state(stateName) */
state(andhraPradesh).
state(arunachalPradesh).
state(assam).
state(bihar).
state(chhattisgarh).
state(goa).
state(gujarat).
state(haryana).
state(himachalPradesh).
state(jharkhand).
state(karnataka).
state(kerala).
state(madhyaPradesh).
state(maharashtra).
state(manipur).
state(meghalaya).
state(mizoram).
state(nagaland).
state(odisha).
state(punjab).
state(rajasthan).
state(sikkim).
state(tamilNadu).
state(telangana).
state(tripura).
state(uttarPradesh).
state(uttarakhand).
state(westBengal).

/* capital(stateName, capitalName) */
capital(andhraPradesh, amaravati).
capital(arunachalPradesh, itanagar).
capital(assam, dispur).
capital(bihar, patna).
capital(chhattisgarh, raipur).
capital(goa, panaji).
capital(gujarat, gandhinagar).
capital(haryana, chandigarh).
capital(himachalPradesh, shimla).
capital(jharkhand, ranchi).
capital(karnataka, bengaluru).
capital(kerala, thiruvananthapuram).
capital(madhyaPradesh, bhopal).
capital(maharashtra, mumbai).
capital(manipur, imphal).
capital(meghalaya, shillong).
capital(mizoram, aizawl).
capital(nagaland, kohima).
capital(odisha, bhubaneswar).
capital(punjab, chandigarh).
capital(rajasthan, jaipur).
capital(sikkim, gangtok).
capital(tamilNadu, chennai).
capital(telangana, hyderabad).
capital(tripura, agartala).
capital(uttarPradesh, lucknow).
capital(uttarakhand, dehradun).
capital(westBengal, kolkata).

/* river(riverName) */
river(ganga).
river(yamuna).
river(brahmaputra).
river(godavari).
river(narmada).
river(krishna).
river(kaveri).
river(mahanadi).
river(tapti).
river(sabarmati).
river(kosi).
river(chambal).
river(sutlej).
river(beas).
river(ravi).
river(chenab).
river(jhelum).
river(son).
river(betwa).
river(ghaggar).
river(tungabhadra).
river(indus).
river(gandak).
river(gomti).
river(brahmani).
river(damodar).
river(subarnarekha).
river(mahi).
river(pennar).
river(periyar).


/* flowsThrough(stateName, riverName) */

flowsThrough(uttarPradesh, ganga).
flowsThrough(bihar, ganga).
flowsThrough(westBengal, ganga).
flowsThrough(uttarakhand, ganga).

flowsThrough(uttarPradesh, yamuna).
flowsThrough(haryana, yamuna).
flowsThrough(delhi, yamuna).
flowsThrough(uttarakhand, yamuna).

flowsThrough(assam, brahmaputra).
flowsThrough(arunachalPradesh, brahmaputra).

flowsThrough(maharashtra, godavari).
flowsThrough(telangana, godavari).
flowsThrough(andhraPradesh, godavari).

flowsThrough(madhyaPradesh, narmada).
flowsThrough(maharashtra, narmada).
flowsThrough(gujarat, narmada).

flowsThrough(maharashtra, krishna).
flowsThrough(karnataka, krishna).
flowsThrough(telangana, krishna).
flowsThrough(andhraPradesh, krishna).

flowsThrough(karnataka, kaveri).
flowsThrough(tamilNadu, kaveri).

flowsThrough(chhattisgarh, mahanadi).
flowsThrough(odisha, mahanadi).

flowsThrough(madhyaPradesh, tapti).
flowsThrough(maharashtra, tapti).
flowsThrough(gujarat, tapti).

flowsThrough(rajasthan, sabarmati).
flowsThrough(gujarat, sabarmati).

flowsThrough(bihar, kosi).

flowsThrough(madhyaPradesh, chambal).
flowsThrough(rajasthan, chambal).
flowsThrough(uttarPradesh, chambal).

flowsThrough(punjab, sutlej).
flowsThrough(himachalPradesh, sutlej).

flowsThrough(punjab, beas).
flowsThrough(himachalPradesh, beas).

flowsThrough(punjab, ravi).
flowsThrough(himachalPradesh, ravi).
flowsThrough(jammuAndKashmir, ravi).

flowsThrough(punjab, chenab).
flowsThrough(jammuAndKashmir, chenab).

flowsThrough(jammuAndKashmir, jhelum).

flowsThrough(madhyaPradesh, son).
flowsThrough(uttarPradesh, son).
flowsThrough(jharkhand, son).
flowsThrough(bihar, son).

flowsThrough(madhyaPradesh, betwa).
flowsThrough(uttarPradesh, betwa).

flowsThrough(haryana, ghaggar).
flowsThrough(punjab, ghaggar).
flowsThrough(rajasthan, ghaggar).

flowsThrough(karnataka, tungabhadra).
flowsThrough(andhraPradesh, tungabhadra).
flowsThrough(telangana, tungabhadra).

flowsThrough(jammuAndKashmir, indus).
flowsThrough(ladakh, indus).

flowsThrough(uttarPradesh, gandak).
flowsThrough(bihar, gandak).

flowsThrough(uttarPradesh, gomti).

flowsThrough(odisha, brahmani).
flowsThrough(jharkhand, brahmani).

flowsThrough(jharkhand, damodar).
flowsThrough(westBengal, damodar).

flowsThrough(jharkhand, subarnarekha).
flowsThrough(westBengal, subarnarekha).
flowsThrough(odisha, subarnarekha).

flowsThrough(madhyaPradesh, mahi).
flowsThrough(rajasthan, mahi).
flowsThrough(gujarat, mahi).

flowsThrough(andhraPradesh, pennar).
flowsThrough(karnataka, pennar).

flowsThrough(kerala, periyar).
flowsThrough(tamilNadu, periyar).


/* spokenIn(stateName, languageName) */

spokenIn(andhraPradesh, telugu).
spokenIn(andhraPradesh, urdu).

spokenIn(arunachalPradesh, nyishi).
spokenIn(arunachalPradesh, adi).
spokenIn(arunachalPradesh, hindi).

spokenIn(assam, assamese).
spokenIn(assam, bengali).
spokenIn(assam, bodo).

spokenIn(bihar, hindi).
spokenIn(bihar, urdu).
spokenIn(bihar, maithili).
spokenIn(bihar, bhojpuri).

spokenIn(chhattisgarh, hindi).
spokenIn(chhattisgarh, chhattisgarhi).
spokenIn(chhattisgarh, gondi).

spokenIn(goa, konkani).
spokenIn(goa, marathi).
spokenIn(goa, portuguese).

spokenIn(gujarat, gujarati).
spokenIn(gujarat, hindi).

spokenIn(haryana, hindi).
spokenIn(haryana, punjabi).
spokenIn(haryana, haryanvi).

spokenIn(himachalPradesh, hindi).
spokenIn(himachalPradesh, pahari).
spokenIn(himachalPradesh, punjabi).

spokenIn(jharkhand, hindi).
spokenIn(jharkhand, santhali).
spokenIn(jharkhand, ho).
spokenIn(jharkhand, mundari).

spokenIn(karnataka, kannada).
spokenIn(karnataka, tulu).
spokenIn(karnataka, kodava).
spokenIn(karnataka, urdu).

spokenIn(kerala, malayalam).
spokenIn(kerala, tamil).

spokenIn(madhyaPradesh, hindi).
spokenIn(madhyaPradesh, malvi).
spokenIn(madhyaPradesh, nimadi).
spokenIn(madhyaPradesh, bhilodi).

spokenIn(maharashtra, marathi).
spokenIn(maharashtra, hindi).
spokenIn(maharashtra, urdu).

spokenIn(manipur, meiteilon).
spokenIn(manipur, thadou).
spokenIn(manipur, tangkhul).

spokenIn(meghalaya, khasi).
spokenIn(meghalaya, garo).
spokenIn(meghalaya, english).

spokenIn(mizoram, mizo).
spokenIn(mizoram, english).

spokenIn(nagaland, english).
spokenIn(nagaland, angami).
spokenIn(nagaland, ao).
spokenIn(nagaland, konyak).

spokenIn(odisha, odia).
spokenIn(odisha, santhali).
spokenIn(odisha, ho).

spokenIn(punjab, punjabi).
spokenIn(punjab, hindi).

spokenIn(rajasthan, hindi).
spokenIn(rajasthan, rajasthani).
spokenIn(rajasthan, marwari).

spokenIn(sikkim, nepali).
spokenIn(sikkim, sikkimese).
spokenIn(sikkim, lepcha).
spokenIn(sikkim, hindi).

spokenIn(tamilNadu, tamil).
spokenIn(tamilNadu, telugu).
spokenIn(tamilNadu, kannada).

spokenIn(telangana, telugu).
spokenIn(telangana, urdu).
spokenIn(telangana, hindi).

spokenIn(tripura, bengali).
spokenIn(tripura, kokborok).
spokenIn(tripura, manipuri).

spokenIn(uttarPradesh, hindi).
spokenIn(uttarPradesh, urdu).
spokenIn(uttarPradesh, awadhi).
spokenIn(uttarPradesh, bhojpuri).

spokenIn(uttarakhand, hindi).
spokenIn(uttarakhand, garhwali).
spokenIn(uttarakhand, kumaoni).

spokenIn(westBengal, bengali).
spokenIn(westBengal, nepali).
spokenIn(westBengal, santali).


/* Languages spoken in the states where river ganga flows. */
languageOnRiver(Language, River) :- flowsThrough(Y, River), spokenIn(Y, Language).
languageOnGanga(Language) :- languageOnRiver(Language, ganga).

/* States through which ganga flows. */
gangaFlowsThrough(State) :- flowsThrough(State, ganga).

/* Capital cities of the states through which Ganga flows. */
flowsThroughCapital(River, Capital) :- flowsThrough(State, River), capital(State, Capital).
gangaFlowsThoughCapital(Capital) :- flowsThroughCapital(ganga, Capital).

/* Find the state through which no river flows. */
stateNoRiver(State) :- state(State), \+ flowsThrough(State, _).

