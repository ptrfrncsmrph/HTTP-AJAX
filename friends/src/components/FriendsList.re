let component = ReasonReact.statelessComponent("FriendsList");

[@bs.deriving jsConverter]
type friend = {
  id: int,
  name: string,
  age: int,
  email: string,
};

[@genType]
let make = (~data: Js.Array.t(friend), _children) => {
  ...component,
  render: _self => {
    <table className="friends">
      <thead>
        <tr>
          {[|"Delete", "Edit", "Name", "Age", "Email"|]
           |> Js.Array.map((field: string) =>
                <th key=field> {field |> ReasonReact.string} </th>
              )
           |> ReasonReact.array}
        </tr>
      </thead>
      <tbody>
        {data
         |> Js.Array.map(({id, name, age, email}: friend) =>
              <tr key={id |> string_of_int}>
                <td>
                  <button className="danger">
                    {"Delete" |> ReasonReact.string}
                  </button>
                </td>
                <td> <button> {"Edit" |> ReasonReact.string} </button> </td>
                <td> {name |> ReasonReact.string} </td>
                <td> {age |> string_of_int |> ReasonReact.string} </td>
                <td> {email |> ReasonReact.string} </td>
              </tr>
            )
         |> ReasonReact.array}
      </tbody>
    </table>;
  },
};