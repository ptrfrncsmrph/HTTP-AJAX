/* TypeScript file generated by genType. */

// tslint:disable-next-line:no-var-requires
const Curry = require('bs-platform/lib/es6/curry.js');

// tslint:disable-next-line:no-var-requires
const FriendsListBS = require('./FriendsList.bs');

// tslint:disable-next-line:no-var-requires
const ReasonReact = require('reason-react/src/ReasonReact.js');

// tslint:disable-next-line:interface-over-type-literal
export type friend = {
  readonly id: number; 
  readonly name: string; 
  readonly age: number; 
  readonly email: string
};

// tslint:disable-next-line:interface-over-type-literal
export type Props = { readonly data: friend[]; readonly children?: unknown };

export const FriendsList: React.ComponentClass<Props> = ReasonReact.wrapReasonForJs(
  FriendsListBS.component,
  (function _(jsProps: Props) {
     return Curry._2(FriendsListBS.make, jsProps.data.map(function _element(ArrayItem: any) { return [ArrayItem.id, ArrayItem.name, ArrayItem.age, ArrayItem.email]}), jsProps.children);
  }));

export default FriendsList;