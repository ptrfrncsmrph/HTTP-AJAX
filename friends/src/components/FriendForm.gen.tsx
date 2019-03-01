/* TypeScript file generated by genType. */

// tslint:disable-next-line:no-var-requires
const Curry = require('bs-platform/lib/es6/curry.js');

// tslint:disable-next-line:no-var-requires
const FriendFormBS = require('./FriendForm.bs');

// tslint:disable-next-line:no-var-requires
const ReasonReact = require('reason-react/src/ReasonReact.js');

import {friend as FriendsList_friend} from './FriendsList.gen';

// tslint:disable-next-line:interface-over-type-literal
export type unvalidatedFriend = {
  readonly name: string; 
  readonly age: string; 
  readonly email: string
};

// tslint:disable-next-line:interface-over-type-literal
export type Props = {
  readonly initState: (null | undefined | FriendsList_friend); 
  readonly handleSubmit: (_1:unvalidatedFriend) => unknown; 
  readonly children?: unknown
};

export const FriendForm: React.ComponentClass<Props> = ReasonReact.wrapReasonForJs(
  FriendFormBS.component,
  (function _(jsProps: Props) {
     return Curry._3(FriendFormBS.make, (jsProps.initState == null ? undefined : jsProps.initState), function _(Arg1: any) {
  const result = jsProps.handleSubmit({name:Arg1[0], age:Arg1[1], email:Arg1[2]});
  return result
}, jsProps.children);
  }));

export default FriendForm;
