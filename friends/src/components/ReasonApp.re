type state =
  | Loading
  | Error
  | Loaded(Js.Array.t(FriendsList.friend));

type action =
  | GetFriends
  | PostFriend(FriendForm.unvalidatedFriend)
  | PutFriend(int, FriendForm.unvalidatedFriend)
  | DeleteFriend(int)
  | ShowError;

let apiEndpoint = "http://10.0.0.53:5000/friends";

let component = ReasonReact.reducerComponent("ReasonApp");

let make = _children => {
  ...component,

  initialState: _state => Loading,

  reducer: action => {
    switch (action) {
    | GetFriends => (
        state => {
          Js.Promise.(
            Axios.get(apiEndpoint)
            |> then_(response => resolve(Js.log(response##data)))
            |> catch(error => resolve(Js.log(error)))
          );
          ReasonReact.Update(state);
        }
      )
    };
  },

  didMount: ({send}) => {
    send(GetFriends);
  },

  render: ({state, send}) => {
    switch (state) {
    | Loading => <div> {"Loading" |> ReasonReact.string} </div>
    | Loaded(data) => <FriendsList data />
    };
  },
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));