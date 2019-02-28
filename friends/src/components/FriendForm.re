type field =
  | Name
  | Age
  | Email;

type action =
  | ChangeField(field, string)
  | Submit;

[@bs.deriving jsConverter]
type state = {
  name: string,
  age: string,
  email: string,
};

let component = ReasonReact.reducerComponent("FriendForm");

[@genType]
let make = (~name, ~age, ~email, ~handleSubmit, _children) => {
  let handleSubmit_ = state => {
    handleSubmit(state->stateToJs);
    Js.log(state->stateToJs);
    ReasonReact.Update({name: "", age: "", email: ""});
  };

  {
    ...component,

    initialState: () => {name, age, email},

    reducer: action => {
      switch (action) {
      | ChangeField(Name, str) => (
          state => ReasonReact.Update({...state, name: str})
        )
      | ChangeField(Age, str) => (
          state => ReasonReact.Update({...state, age: str})
        )
      | ChangeField(Email, str) => (
          state => ReasonReact.Update({...state, email: str})
        )
      | Submit => handleSubmit_
      };
    },

    render: ({state, send}) => {
      let {name, age, email} = state;
      <form
        onSubmit={e => {
          ReactEvent.Form.preventDefault(e);
          send(Submit);
        }}>
        <div className="input-container">
          <label>
            {"Name" |> ReasonReact.string}
            <input
              value=name
              onChange={e =>
                send(ChangeField(Name, ReactEvent.Form.target(e)##value))
              }
            />
          </label>
          <label>
            {"Age" |> ReasonReact.string}
            <input
              value=age
              onChange={e =>
                send(ChangeField(Age, ReactEvent.Form.target(e)##value))
              }
            />
          </label>
          <label>
            {"Email" |> ReasonReact.string}
            <input
              value=email
              onChange={e =>
                send(ChangeField(Email, ReactEvent.Form.target(e)##value))
              }
            />
          </label>
        </div>
        <button> {"Submit" |> ReasonReact.string} </button>
      </form>;
    },
  };
};