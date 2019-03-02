type field =
  | Name
  | Age
  | Email;

type action =
  | ChangeField(field, string)
  | Submit;

[@bs.deriving jsConverter]
type validatedFriend = {
  name: string,
  age: int,
  email: string,
};

type unvalidatedFriend = {
  name: string,
  age: string,
  email: string,
};

type retainedProps = {initState: unvalidatedFriend};

let emptyFriend: unvalidatedFriend = {name: "", email: "", age: ""};

let toUnvalidated =
    ({name, email, age: age_}: FriendsList.friend): unvalidatedFriend => {
  {name, email, age: string_of_int(age_)};
};

let component = ReasonReact.reducerComponentWithRetainedProps("FriendForm");

let make = (~initState=emptyFriend, ~handleSubmit, _children) => {
  {
    ...component,

    initialState: () => emptyFriend,

    retainedProps: initState,

    willReceiveProps: self =>
      if (self.retainedProps == initState) {
        initState;
      } else {
        initState;
      },

    reducer: (action, state) => {
      switch (action) {
      | ChangeField(Name, str) => ReasonReact.Update({...state, name: str})
      | ChangeField(Age, str) => ReasonReact.Update({...state, age: str})
      | ChangeField(Email, str) => ReasonReact.Update({...state, email: str})
      | Submit =>
        handleSubmit(state);
        ReasonReact.Update(emptyFriend);
      };
    },

    didMount: _ => {
      Js.log("Mounted");
    },

    render: self => {
      let {name, age, email} = self.state;
      <form
        onSubmit={e => {
          ReactEvent.Form.preventDefault(e);
          self.send(Submit);
        }}>
        <div className="input-container">
          <label>
            {"Name" |> ReasonReact.string}
            <input
              value=name
              onChange={e =>
                self.send(
                  ChangeField(Name, ReactEvent.Form.target(e)##value),
                )
              }
            />
          </label>
          <label>
            {"Age" |> ReasonReact.string}
            <input
              value=age
              onChange={e =>
                self.send(
                  ChangeField(Age, ReactEvent.Form.target(e)##value),
                )
              }
            />
          </label>
          <label>
            {"Email" |> ReasonReact.string}
            <input
              value=email
              onChange={e =>
                self.send(
                  ChangeField(Email, ReactEvent.Form.target(e)##value),
                )
              }
            />
          </label>
        </div>
        <button> {"Submit" |> ReasonReact.string} </button>
      </form>;
    },
  };
};