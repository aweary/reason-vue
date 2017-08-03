/* The abstract type for the global Vue object */
type vue;

/* A merge strategy is used by config.optionalMergeStrategies */
type mergeStategy = string => string => vue => unit;

/* Error handlers are defined on Vue.config.errorHandler */
/* @TODO are these types right? */
type errorHandler = string => vue => string => unit;

/* Error handlers are defined on Vue.config.warnHandler */
/* @TODO are these types right? */
type warnHandler = string => vue => string => unit;

/* An ignored element is a string representing a DOM element
   That is being ignored by Vue. Usually a web component */
type ignoredElement = string;

/* Keycode variant */
type keyCode =
  | KeyCode int
  | KeyCodes (Js.Array.t int);

/* Keycode dictionary */
type keyCodes = Js.Dict.t keyCode;

/* The actual value for the global Vue object */
external vue : vue = "" [@@bs.module];

/* Top-level config options set/get on Vue.config  */
/* Get/set Vue.config.silent */
external setSilent' : vue => Js.boolean => unit = "silent" [@@bs.scope "config"] [@@bs.set];

external getSilent : vue => Js.boolean = "silent" [@@bs.scope "config"] [@@bs.get];

/* Helper utility so config setting can be chained */
let setSilent silent vue => {
  setSilent' vue silent;
  vue
};

/* Get/set Vue.config.devtools */
external setDevtools' : vue => Js.boolean => unit = "devtools" [@@bs.scope "config"] [@@bs.set];

external getDevtools : vue => Js.boolean = "devtools" [@@bs.scope "config"] [@@bs.get];

/* Helper utility so config setting can be chained */
let setDevtools devtools vue => {
  setDevtools' vue devtools;
  vue
};

/* Get/set Vue.config.errorHandler */
external setErrorHandler' : vue => errorHandler => unit =
  "errorHandler" [@@bs.scope "config"] [@@bs.set];

external getErrorHandler : vue => Js.Undefined.t errorHandler =
  "errorHandler" [@@bs.scope "config"] [@@bs.get];

/* Hepler utiltiy so config setting can be chained */
let setErrorHandler errorHandler vue => {
  setErrorHandler' vue errorHandler;
  vue
};

/* Get/set Vue.config.warnHandler */
external setWarnHandler' : vue => warnHandler => unit =
  "warnHandler" [@@bs.scope "config"] [@@bs.set];

external getWarnHandler : vue => Js.Undefined.t warnHandler =
  "warnHandler" [@@bs.scope "config"] [@@bs.get];

/* Hepler utiltiy so config setting can be chained */
let setWarnHandler warnHandler vue => {
  setWarnHandler' vue warnHandler;
  vue
};

/* Get/set for Vue.config.ignoredElements */
external setIgnoredElements' : vue => Js.Array.t ignoredElement => unit =
  "ignoredElements" [@@bs.scope "config"] [@@bs.set];

external getIgnoredElements : vue => Js.Array.t ignoredElement =
  "ignoredElements" [@@bs.scope "config"] [@@bs.get];

/* Helper utility so config setting can be chained */
let setIgnoredElements ignoredElements vue => {
  setIgnoredElements' vue ignoredElements;
  vue
};

/* TODO move this into a KeyCode module */
external setKeyCodes' : vue => keyCodes => unit = "keyCodes" [@@bs.scope "config"] [@@bs.set];
external getKeyCodes : vue => keyCodes = "keyCodes" [@@bs.scope "config"] [@@bs.get];
let setKeyCodes keyCodes vue => {
  setKeyCodes' vue keyCodes;
  vue
};
let makeKeyCodes () :keyCodes => Js.Dict.empty ();
let setKeyCodePair key (value: keyCode) keyCodes => {
  Js.Dict.set keyCodes key value;
  keyCodes
};

setKeyCodes ((makeKeyCodes ())
|> setKeyCodePair "foo" (KeyCode 52)
|> setKeyCodePair "foo" (KeyCode 52)
|> setKeyCodePair "foo" (KeyCode 52)) vue;


/* Get/set for Vue.config.performance */

external setPerformance' : vue => Js.boolean => unit = "performance" [@@bs.scope "config"] [@@bs.set];
external getPerformance : vue => Js.boolean = "performance" [@@bs.scope "config"] [@@bs.get];

let setPerformance value vue => {
  setPerformance' vue value;
  vue
};

/* Get/set for Vue.config.productionTip */

external setProductionTip' : vue => Js.boolean => unit = "productionTip" [@@bs.scope "config"] [@@bs.set];
external getProductionTip : vue => Js.boolean = "productionTip" [@@bs.scope "config"] [@@bs.get];

let setProductionTip value vue => {
  setProductionTip' vue value;
  vue
};

/*
 ====================================
 ============ TESTING ===============
 ====================================
 */


 let errorHandler err vm info => {
   Js.log err;
 };

 let warnHandler msg vm trace => {
   Js.log msg;
 };

 vue
 |> setSilent Js.true_
 |> setDevtools Js.false_
 |> setErrorHandler errorHandler
 |> setWarnHandler warnHandler
 |> setIgnoredElements [||]
 |> setPerformance Js.true_;

  